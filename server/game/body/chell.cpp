//
// Created by franciscosicardi on 25/05/19.
//

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Dynamics/Joints/b2WheelJoint.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include "chell.h"
#include "../ray_cast_callback/portal_ray_cast_callback.h"

#define JUMP_TIMEOUT 100

void Chell::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(xPos, yPos);
    bodyDef.fixedRotation = true;
    body = world.CreateBody(&bodyDef);
    body->SetUserData(this);

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

    b2PolygonShape sensorShape;
    sensorShape.SetAsBox(0.1, 0.1, b2Vec2(0, -0.70), 0);

    b2FixtureDef sensorFixtureDef;
    sensorFixtureDef.shape = &sensorShape;
    sensorFixtureDef.isSensor = true;
    sensorFixtureDef.userData = (void *)CONTACT_CHECK;

    body->CreateFixture(&sensorFixtureDef);

    hx = 0.175f;
    hy = 0.65f;
}

Chell::Chell(b2World &world, float32 xPos, float32 yPos, uint32_t playerId, Portal *bluePortal, Portal *orangePortal,
             float32 maxReach) :
             Body(world, xPos, yPos, playerId), portals(), state(STOP), alive(true), footContacts(0),
             jumpTimer(), maxReach(maxReach), carriesRock(false), rock(nullptr), grabbedRockUpdated(false),
             threwRockUpdated(false), forceThrew(false), _justDied(false) {
    connect(bluePortal, orangePortal);
    portals[BLUE] = bluePortal;
    portals[ORANGE] = orangePortal;
    createBody(xPos, yPos);
}

Chell::~Chell() {
    delete portals[BLUE];
    delete portals[ORANGE];
}

void Chell::updateState(chell_state_t state) {
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
                applyImpulse(vel.x, 6.0f);
                state = AIR;
                jumpTimer.Reset();
            }
            break;
        case LEFT:
            printf("move left\n");
            applyImpulse(-3.0f, vel.y);
            break;
        case RIGHT:
            printf("move right\n");
            applyImpulse(3.0f, vel.y);
            break;
        case STOP:
            applyImpulse(0, vel.y);
            break;
    }
}

bool Chell::isJumping() {
    return footContacts == 0 || jumpTimer.GetMilliseconds() < JUMP_TIMEOUT;
}

Portal *Chell::getPortal(portal_color_t color) {
    return portals[color];
}

body_type_t Chell::getBodyType() {
    return CHELL;
}

bool Chell::isAlive() {
    return alive;
}

void Chell::die() {
    alive = false;
    _justDied = true;
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
                portals[color]->moveTo(position.x, position.y);
                portals[color]->setNormal(portalRaycastCallback->getNormal());
            }
            delete portalRaycastCallback;
            return;
        }
    direction = 1.25f * direction;
    }
}

void Chell::grabRock() {
    if (carriesRock) {
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

void Chell::throwRock(bool force) {
    if (!carriesRock) return;
    threwRockUpdated = true;
    forceThrew = force;
}

bool Chell::grabIfRock(Body *body) {
    if (body->getBodyType() == ROCK) {
        carriesRock = true;
        rock = dynamic_cast<Rock *>(body);
        grabbedRockUpdated = true;
        return true;
    }
    return false;
}

bool Chell::grabbedRock() {
    if (!carriesRock)
        return false;
    bool updated = grabbedRockUpdated;
    grabbedRockUpdated = false;
    rock->setActive(false);
    return updated;
}

Rock *Chell::getRock() {
    return rock;
}

bool Chell::threwRock() {
    if (!carriesRock)
        return false;
    bool updated = threwRockUpdated;
    threwRockUpdated = false;
    if (updated) {
        rock->setActive(true);
        if (forceThrew) {
            rock->moveToInitial();
            forceThrew = false;
        } else {
            rock->moveTo(getXPos(), getYPos() + hy + rock->hy);
        }
        carriesRock = false;
    }
    return updated;
}

bool Chell::justDied() {
    if (_justDied) {
        _justDied = false;
        body->SetActive(false);
        return true;
    }
    return false;
}

Chell::Chell(Chell &&other) noexcept: Body(std::move(other)), portals(), state(other.state), alive(other.alive),
                                      footContacts(other.footContacts), jumpTimer(other.jumpTimer), maxReach(other.maxReach),
                                      carriesRock(other.carriesRock), rock(other.rock), grabbedRockUpdated(other.grabbedRockUpdated),
                                      threwRockUpdated(other.threwRockUpdated), forceThrew(other.forceThrew), _justDied(other._justDied) {
    portals[0] = other.portals[0];
    portals[1] = other.portals[1];
    other.portals[0] = nullptr;
    other.portals[1] = nullptr;
}
