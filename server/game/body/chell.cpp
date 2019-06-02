//
// Created by franciscosicardi on 25/05/19.
//

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "chell.h"

void Chell::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(xPos, yPos);
    body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.5f, 0.75f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

Chell::Chell(b2World &world, float32 xPos, float32 yPos, uint32_t playerId):
             Body(world, xPos, yPos, playerId), state(STOP), jump_state(false) {
    createBody(xPos, yPos);
}

Chell::~Chell() = default;

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
    float32 yVel = vel.y;
    if (jump_state && isNotJumping()) {
        printf("jump\n");
        yVel = 7.0f;
    }
    jump_state = false;
    switch (state) {
        case LEFT:
            printf("move left\n");
            move(-3.0f, yVel);
            break;
        case RIGHT:
            printf("move right\n");
            move(3.0f, yVel);
            break;
        case STOP:
            if (vel.x != 0 || yVel != 0) {
                move(0.0f, yVel);
            }
            break;
    }
}

bool Chell::isNotJumping() {
    float32 velY = body->GetLinearVelocity().y;
    return velY < 0.2 && velY > -0.2;
}


