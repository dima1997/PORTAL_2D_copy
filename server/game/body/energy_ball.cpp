//
// Created by franciscosicardi on 20/06/19.
//

#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include "energy_ball.h"

#define VEL 2.0f

void EnergyBall::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    bodyDef.type = b2_dynamicBody;
    bodyDef.gravityScale = 0;
    bodyDef.fixedRotation = true;
    body = world.CreateBody(&bodyDef);
    body->SetUserData(this);
    b2CircleShape circle;
    circle.m_radius = 0.1;
    body->CreateFixture(&circle, 0.1f);
}

EnergyBall::EnergyBall(b2World &world, float32 xPos, float32 yPos, uint32_t id, EnergyEmitter &emitter):
                       Body(world, xPos, yPos, id), emitter(emitter) {
    createBody(xPos, yPos);
    resetDirection();
    b2Vec2 final = VEL * direction;
    applyImpulse(final.x, final.y);
}

EnergyBall::EnergyBall(const EnergyBall &other): Body(other), emitter(other.emitter), direction(other.direction) {}

body_type_t EnergyBall::getBodyType() {
    return ENERGY_BALL;
}

void EnergyBall::resetDirection() {
    direction_t dir = emitter.getDirection();
    switch (dir) {
        case UP_D:
            direction = b2Vec2(0, 1);
            break;
        case DOWN_D:
            direction = b2Vec2(0, -1);
            break;
        case RIGHT_D:
            direction = b2Vec2(1, 0);
            break;
        case LEFT_D:
            direction = b2Vec2(-1, 0);
            break;
    }
}

void EnergyBall::move() {
    b2Vec2 final = VEL * direction;
    applyImpulse(final.x, final.y);
}

void EnergyBall::setDirection(b2Vec2 dir) {
    dir.Normalize();
    direction = dir;
}

b2Vec2 EnergyBall::getDirection() {
    return direction;
}


EnergyBall::~EnergyBall() = default;
