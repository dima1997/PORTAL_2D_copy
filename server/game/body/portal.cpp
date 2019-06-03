//
// Created by franciscosicardi on 02/06/19.
//

#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include "portal.h"

Portal::Portal(b2World &world, float32 xPos, float32 yPos, uint32_t id):
               Body(world, xPos, yPos, id), other() {
    createBody(xPos, yPos);
}

void connect(Portal *portal1, Portal *portal2) {
    portal1->other = portal2;
    portal2->other = portal1;
}

void Portal::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    body = world.CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = 0.50f;

    b2FixtureDef circleFixtureDef;
    circleFixtureDef.shape = &circleShape;

    body->CreateFixture(&circleFixtureDef);
}

void Portal::moveTo(float32 x, float32 y) {
    body->SetTransform(b2Vec2(x, y), body->GetAngle());
}

Portal::~Portal() = default;

