//
// Created by franciscosicardi on 25/05/19.
//

#include "body.h"

bool is_movable(body_type_t bodyType) {
    return bodyType == CHELL || bodyType == ROCK || bodyType == ENERGY_BALL;
}

Body::Body(b2World &world, float32 xPos, float32 yPos, uint32_t id): lastPosition(xPos, yPos),
           id(id), world(world), body(), hx(), hy() {
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    bodyDef.fixedRotation = true;
    bodyDef.userData = this;
    body = world.CreateBody(&bodyDef);
    customizeBody();
}

uint32_t Body::getId() {
    return id;
}

float32 Body::getXPos() {
    return lastPosition.x;
}

float32 Body::getYPos() {
    return lastPosition.y;
}

Body::Body(const Body &other): lastPosition(other.lastPosition), id(other.id), world(other.world), body(other.body),
                               hx(other.hx), hy(other.hy) {
    body->SetUserData(this);
}

void Body::customizeBody() {}

Body::~Body() = default;
