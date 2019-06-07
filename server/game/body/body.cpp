//
// Created by franciscosicardi on 25/05/19.
//

#include "body.h"
#include "../../utils/id_generator.h"

Body::Body(b2World &world, float32 xPos, float32 yPos, uint32_t id):
            manually_updated(false), lastPosition(xPos, yPos), id(id), world(world), body() {}

bool Body::changedPosition() {
    if (manually_updated) {
        body->SetTransform(b2Vec2(lastPosition.x, lastPosition.y), body->GetAngle());
        manually_updated = false;
//        body->SetActive(true);
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
//    body->SetActive(false);
    lastPosition = b2Vec2(x, y);
    manually_updated = true;
//    body->SetTransform(b2Vec2(x, y), body->GetAngle());
}

Body::~Body() = default;
