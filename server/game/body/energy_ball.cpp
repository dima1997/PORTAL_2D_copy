//
// Created by franciscosicardi on 20/06/19.
//

#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include "energy_ball.h"

void EnergyBall::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    bodyDef.type = b2_dynamicBody;
    bodyDef.gravityScale = 0;
    body = world.CreateBody(&bodyDef);
    body->SetUserData(this);
    b2CircleShape circle;
    circle.m_radius = 0.1;
    body->CreateFixture(&circle, 0.1f);
}

EnergyBall::EnergyBall(b2World &world, float32 xPos, float32 yPos, uint32_t id, EnergyEmitter &emitter):
                       Body(world, xPos, yPos, id), emitter(emitter) {
    createBody(xPos, yPos);
}

body_type_t EnergyBall::getBodyType() {
    return ENERGY_BALL;
}

EnergyBall::~EnergyBall() = default;
