//
// Created by franciscosicardi on 02/06/19.
//

#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include "portal.h"

Portal::Portal(b2World &world, float32 xPos, float32 yPos, uint32_t id):
               Body(world, xPos, yPos, id), other(), usable(true) {
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
    body->SetUserData(this);

    b2CircleShape circleShape;
    circleShape.m_radius = 0.50f;

    b2FixtureDef circleFixtureDef;
    circleFixtureDef.shape = &circleShape;

    body->CreateFixture(&circleFixtureDef);
}

void Portal::startGoingThrough(Body *body) {
    if (!usable)
        return;
    body->moveTo(other->getXPos(), other->getYPos());

    float32 angle = acos(b2Dot(this->normal, other->normal)/(this->normal.Length() * other->normal.Length()));
    float32 cs = cosf(angle);
    float32 sn = sinf(angle);

    b2Vec2 currentVel = body->getCurrentVelocity();

    float32 newX = currentVel.x * cs - currentVel.y * sn;
    float32 newY = currentVel.x * sn + currentVel.y * cs;
    body->updateVelocity(newX, newY);
    other->usable = false;
}

body_type_t Portal::getBodyType() {
    return PORTAL;
}

void Portal::endGoingThrough() {
    usable = true;
}

void Portal::setNormal(b2Vec2 normal) {
    this->normal = normal;
}

Portal::~Portal() = default;

