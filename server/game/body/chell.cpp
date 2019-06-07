//
// Created by franciscosicardi on 25/05/19.
//

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Dynamics/Joints/b2WheelJoint.h>
#include "chell.h"
#include "../ray_cast_callback/portal_ray_cast_callback.h"

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
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    b2CircleShape circleShape;
    circleShape.m_p.Set(0, -0.4f);
    circleShape.m_radius = 0.35;

    b2FixtureDef circleFixtureDef;
    circleFixtureDef.shape = &circleShape;
    circleFixtureDef.density = 0.5;
    circleFixtureDef.friction = 0.3f;

    body->CreateFixture(&circleFixtureDef);
    }

Chell::Chell(b2World &world, float32 xPos, float32 yPos, uint32_t playerId, Portal *bluePortal, Portal *orangePortal):
             Body(world, xPos, yPos, playerId), portals(),
             state(STOP), jump_state(false), alive(true) {
    connect(bluePortal, orangePortal);
    portals[BLUE] = bluePortal;
    portals[ORANGE] = orangePortal;
    createBody(xPos, yPos);
}

Chell::~Chell() {
    delete portals[BLUE];
    delete portals[ORANGE];
}

void Chell::move(float32 xSpeed, float32 ySpeed) {
    b2Vec2 vel = body->GetLinearVelocity();
    float32 dvx = xSpeed - vel.x;
    float32 dvy = ySpeed - vel.y;
    float32 mass = body->GetMass();
    body->ApplyLinearImpulseToCenter(b2Vec2(mass * dvx, mass * dvy), true);
}

void Chell::jump() {
    jump_state = true;
}

void Chell::updateState(chell_state_t state) {
    this->state = state;
}

void Chell::update() {
    const b2Vec2 &vel = body->GetLinearVelocity();
    float32 jumpVel = vel.y;
    if (jump_state && !isJumping()) {
        printf("jump\n");
        jumpVel = 7.0f;
    }
    jump_state = false;
    switch (state) {
        case LEFT:
            printf("move left\n");
            move(-3.0f, jumpVel);
            break;
        case RIGHT:
            printf("move right\n");
            move(3.0f, jumpVel);
            break;
        case STOP:
            if (isJumping()) {
                move(vel.x, jumpVel);
            } else {
                move(0, jumpVel);
            }
            break;
    }
}

bool Chell::isJumping() {
    float32 velY = body->GetLinearVelocity().y;
    return velY > 0.2 || velY < -0.2;
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
}

void Chell::shootPortal(float x, float y, portal_color_t color) {
    auto portalRaycastCallback = new PortalRaycastCallback();
    world.RayCast(portalRaycastCallback, body->GetPosition(), b2Vec2(x, y));
    b2Fixture *fixture = portalRaycastCallback->getFixture();
    if (fixture == nullptr)
        return;
    Body *body = (Body *)fixture->GetBody()->GetUserData();
    if (body->getBodyType() == METAL_BLOCK) {
        b2Vec2 position = portalRaycastCallback->getPoint();
        portals[color]->moveTo(position.x, position.y);
        portals[color]->setNormal(portalRaycastCallback->getNormal());
    }
    delete portalRaycastCallback;
}
