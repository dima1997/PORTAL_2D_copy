//
// Created by franciscosicardi on 25/05/19.
//

#include "body.h"
#include "../id_generator.h"

Body::Body(b2World &world, float32 xPos, float32 yPos):
           id(IdGenerator::getNewId()), updated(false), lastPosition(xPos, yPos), world(world), body() {}

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

uint32_t Body::getId() {
    return id;
}

Body::~Body() = default;
