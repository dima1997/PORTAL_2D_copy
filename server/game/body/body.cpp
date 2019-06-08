//
// Created by franciscosicardi on 25/05/19.
//

#include "body.h"
#include "../../utils/id_generator.h"

Body::Body(b2World &world, float32 xPos, float32 yPos, uint32_t id):
           id(id), updated_position(false), updated_velocity(false), lastPosition(xPos, yPos), lastVelocity(0, 0), world(world), body() {}

bool Body::changedPositionOrVelocity() {
    bool status = false;
    if (updated_position) {
        body->SetTransform(lastPosition, body->GetAngle());
        updated_position = false;
        status = true;
    } else if (lastPosition.x != body->GetPosition().x || lastPosition.y != body->GetPosition().y) {
        lastPosition = body->GetPosition();
        status = true;
    }

    if (updated_velocity) {
        body->SetLinearVelocity(lastVelocity);
        updated_velocity = false;
        status = true;
    } else if (lastVelocity != body->GetLinearVelocity()) {
        lastVelocity = body->GetLinearVelocity();
    }
    return status;
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
