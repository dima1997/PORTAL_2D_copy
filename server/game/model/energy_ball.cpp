//
// Created by franciscosicardi on 20/06/19.
//

#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include "energy_ball.h"
#include "../../config/global_configuration.h"

void EnergyBall::customizeBody() {
    body->SetGravityScale(0);
    b2CircleShape circle;
    circle.m_radius = 0.1;
    body->CreateFixture(&circle, 0.0f);
}

EnergyBall::EnergyBall(b2World &world, float32 xPos, float32 yPos, uint32_t id, EnergyEmitter &emitter):
                       MovableBody(world, xPos, yPos, id), emitter(emitter), timer() {
    customizeBody();
    resetDirection();
    b2Vec2 final = CONFIG.energy_ball_speed * direction;
    applyImpulse(final.x, final.y);
}

EnergyBall::EnergyBall(const EnergyBall &other): MovableBody(other), emitter(other.emitter), direction(other.direction),
                                                 timer(other.timer) {}

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
    if (timer.GetMilliseconds() >= CONFIG.energy_ball_reset_time_milliseconds) {
        resetPosition();
        return;
    }
    b2Vec2 final = CONFIG.energy_ball_speed * direction;
    applyImpulse(final.x, final.y);
}

void EnergyBall::setDirection(b2Vec2 dir) {
    dir.Normalize();
    direction = dir;
}

b2Vec2 EnergyBall::getDirection() {
    return direction;
}

void EnergyBall::resetPosition() {
    resetDirection();
    timer.Reset();
    moveTo(emitter.getXPos(), emitter.getYPos());
}

void EnergyBall::_applyImpulse(float32 xSpeed, float32 ySpeed) {
    setDirection(b2Vec2(xSpeed, ySpeed));
    MovableBody::_applyImpulse(xSpeed, ySpeed);
}


EnergyBall::~EnergyBall() = default;
