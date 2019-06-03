//
// Created by franciscosicardi on 25/05/19.
//

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Dynamics/Joints/b2WheelJoint.h>
#include "chell.h"

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

Chell::Chell(b2World &world, float32 xPos, float32 yPos, uint32_t playerId):
             Body(world, xPos, yPos, playerId), state(STOP), jump_state(false) {
    createBody(xPos, yPos);
}

Chell::~Chell() {
    delete orangePortal;
    delete bluePortal;
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

void Chell::setOrangePortal(Portal *portal) {
    orangePortal = portal;
}

void Chell::setBluePortal(Portal *portal) {
    bluePortal = portal;
}

void Chell::moveBluePortal(float32 x, float32 y) {
    bluePortal->moveTo(x, y);
}

void Chell::moveOrangePortal(float32 x, float32 y) {
    orangePortal->moveTo(x, y);
}

Portal *Chell::getOrangePortal() {
    return orangePortal;
}

Portal *Chell::getBluePortal() {
    return bluePortal;
}

body_type_t Chell::getBodyType() {
    return CHELL;
}


