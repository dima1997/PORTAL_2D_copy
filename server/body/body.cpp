//
// Created by franciscosicardi on 25/05/19.
//

#include "body.h"

Body::Body(uint32_t id, b2World &world, float32 xPos, float32 yPos):
           id(id), updated(false), lastPosition(xPos, yPos), world(world), body() {}

bool Body::isUpdated() {
    return updated;
}

void Body::update(b2Vec2 pos) {
    if (lastPosition.x != pos.x || lastPosition.y != pos.y) {
        lastPosition = pos;
        updated = true;
    } else {
        updated = false;
    }
}

Body::~Body() = default;
