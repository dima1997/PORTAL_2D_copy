//
// Created by franciscosicardi on 25/05/19.
//

#include "body.h"
#include "../../utils/id_generator.h"

Body::Body(b2World &world, float32 xPos, float32 yPos, uint32_t id):
           id(id), updated_position(false), updated_velocity(false), lastPosition(xPos, yPos), lastVelocity(0, 0), world(world), body() {}

bool Body::changedPositionOrVelocity() {
    if (updated_position) {
        body->SetTransform(b2Vec2(lastPosition), body->GetAngle());
        updated_position = false;
        return true;
    }
    if (updated_velocity) {
        body->SetLinearVelocity(b2Vec2(lastVelocity));
        updated_velocity = false;
        return true;
    }
    if (lastPosition.x != body->GetPosition().x || lastPosition.y != body->GetPosition().y) {
        lastPosition = body->GetPosition();
        return true;
    }
    return false;
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

void Body::moveTo(float32 x, float32 y) {
    lastPosition = b2Vec2(x, y);
    updated_position = true;
}

void Body::updateVelocity(float32 x, float32 y) {
    lastVelocity = b2Vec2(x, y);
    updated_velocity = true;
}

b2Vec2 Body::getCurrentVelocity() {
    return body->GetLinearVelocity();
}

Body::~Body() = default;
