//
// Created by franciscosicardi on 25/05/19.
//

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Dynamics/Joints/b2WheelJoint.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <sys/socket.h>
#include "chell.h"
#include "../ray_cast_callback/portal_ray_cast_callback.h"
#include "portal.h"
#include "../../config/global_configuration.h"

void Chell::customizeBody() {

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.35f, 0.5f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.1f;

    body->CreateFixture(&fixtureDef);

    b2CircleShape circleShape;
    circleShape.m_p.Set(0, -0.4f);
    circleShape.m_radius = 0.35;

    b2FixtureDef circleFixtureDef;
    circleFixtureDef.shape = &circleShape;
    circleFixtureDef.density = 0.5;
    circleFixtureDef.friction = 0.3f;

    body->CreateFixture(&circleFixtureDef);

    b2FixtureDef sensorFixtureDef;
    sensorFixtureDef.shape = &circleShape;
    sensorFixtureDef.isSensor = true;
    sensorFixtureDef.userData = (void *)CONTACT_CHECK;

    body->CreateFixture(&sensorFixtureDef);

    hx = 0.175f;
    hy = 0.65f;
}

Chell::Chell(b2World &world, float32 xPos, float32 yPos, uint32_t playerId, Portal &bluePortal, Portal &orangePortal,
             PinTool &pinTool, float32 maxReach) :
             MovableBody(world, xPos, yPos, playerId), portals{bluePortal, orangePortal}, pinTool(pinTool), state(STOP),
             footContacts(0), jumpTimer(), maxReach(maxReach), rock(nullptr), rockStateUpdated(false),
             threwRockUpdated(false), rockState(NO_ROCK), throughPortal(false), gameState(PLAYING_C) {
    connect(bluePortal, orangePortal);
    customizeBody();
}

Chell::~Chell() = default;

void Chell::updateState(move_state_t state) {
    if (this->state != AIR && this->state != JUMP) {
        this->state = state;
    }
}

void Chell::update() {
    const b2Vec2 &vel = body->GetLinearVelocity();
    switch (state) {
        case AIR:
            applyImpulse(vel.x, vel.y);
            if (!isJumping() && !throughPortal) {
                state = STOP;
            }
            break;
        case JUMP:
            if (!isJumping()) {
                applyImpulse(vel.x, CONFIG.chellJumpSpeed);
                state = AIR;
                jumpTimer.Reset();
            }
            break;
        case LEFT:
            applyImpulse(-CONFIG.chellMoveSpeed, vel.y);
            break;
        case RIGHT:
            applyImpulse(CONFIG.chellMoveSpeed, vel.y);
            break;
        case STOP:
            applyImpulse(0, vel.y);
            break;
    }
}

bool Chell::isJumping() {
    return footContacts == 0 || jumpTimer.GetMilliseconds() < CONFIG.chellJumpTimeoutMilliseconds;
}

Portal &Chell::getPortal(portal_color_t color) {
    return portals[color];
}

body_type_t Chell::getBodyType() {
    return CHELL;
}

void Chell::die() {
    gameState = DIED_C;
    throwRock(THROW_IN);
    resetPortals();
}

void Chell::shootPortal(float x, float y, portal_color_t color) {
    auto portalRaycastCallback = new PortalRaycastCallback(this);
    b2Vec2 direction = b2Vec2(x, y);
    b2Fixture *fixture;
    while (direction.Length() < maxReach) {
        world.RayCast(portalRaycastCallback, body->GetPosition(), direction);
        fixture = portalRaycastCallback->getFixture();
        if (fixture != nullptr) {
            Body *body = (Body *)fixture->GetBody()->GetUserData();
            if (body->getBodyType() == METAL_BLOCK) {
                b2Vec2 position = portalRaycastCallback->getPoint();
                portals[color].moveTo(position.x, position.y);
                portals[color].setNormal(portalRaycastCallback->getNormal());
                portals[color].showAndActivateIfRequires();
            }
            delete portalRaycastCallback;
            return;
        }
    direction = 1.25f * direction;
    }
}

void Chell::grabRock() {
    if (rockState != NO_ROCK) {
        return;
    }
    for (b2ContactEdge *contactEdge = body->GetContactList(); contactEdge != nullptr; contactEdge = contactEdge->next) {
        b2Contact *contact = contactEdge->contact; 
        if (!contact->IsTouching()) continue;
        Body *body = (Body *) contact->GetFixtureA()->GetBody()->GetUserData();
        if (grabIfRock(body)) {
            return;
        }
        body = (Body *) contact->GetFixtureB()->GetBody()->GetUserData();
        grabIfRock(body);
    }
}

void Chell::throwRock(rock_state_t rock_state) {
    if (rockState != HAS_ROCK) return;
    threwRockUpdated = true;
    rockState = rock_state;
}

bool Chell::grabIfRock(Body *body) {
    if (body->getBodyType() == ROCK) {
        rockState = HAS_ROCK;
        rock = dynamic_cast<Rock *>(body);
        rockStateUpdated = true;
        return true;
    }
    return false;
}

bool Chell::grabbedRock() {
    if (rockState != HAS_ROCK)
        return false;
    bool updated = rockStateUpdated;
    rockStateUpdated = false;
    rock->setActive(false);
    return updated;
}

Rock &Chell::getRock() {
    return *rock;
}

bool Chell::threwRock() {
    if (rockState == HAS_ROCK || rockState == NO_ROCK)
        return false;
    bool updated = threwRockUpdated;
    threwRockUpdated = false;
    if (updated) {
        rock->setActive(true);
        if (rockState == THROW_IN) {
            rock->moveTo(getXPos(), getYPos());
        } else if (rockState == THROW_INITIAL) {
            rock->moveToInitial();
        } else if (rockState == THROW_LEFT) {
                rock->moveTo(getXPos() - hx - rock->hx, getYPos());
        } else if (rockState == THROW_RIGHT) {
            rock->moveTo(getXPos() + hx + rock->hx, getYPos());
        }
        rockState = NO_ROCK;
    }
    return updated;
}

Chell::Chell(const Chell &other): MovableBody(other), portals{other.portals[BLUE], other.portals[ORANGE]},
                                  pinTool(other.pinTool), state(other.state), footContacts(other.footContacts),
                                  jumpTimer(other.jumpTimer), maxReach(other.maxReach),
                                  rock(other.rock), rockStateUpdated(other.rockStateUpdated),
                                  threwRockUpdated(other.threwRockUpdated), throughPortal(other.throughPortal),
                                  rockState(other.rockState), gameState(other.gameState) {
    connect(portals[BLUE], portals[ORANGE]);
}

void Chell::resetPortals() {
    portals[BLUE].hideAndDeactivate();
    portals[ORANGE].hideAndDeactivate();
}

void Chell::showPinTool(float32 x, float32 y) {
    pinTool.show(x, y);
}

PinTool &Chell::getPinTool() {
    return pinTool;
}

bool Chell::_changedPosition() {
    update();
    return MovableBody::_changedPosition();
}

chell_state_t Chell::getState() {
    return gameState;
}

void Chell::reachCake() {
    gameState = REACHED_CAKE_C;
}

void Chell::finish() {
    gameState = FINISHED_C;
    body->SetActive(false);
}
