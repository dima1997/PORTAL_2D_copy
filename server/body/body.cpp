//
// Created by franciscosicardi on 25/05/19.
//

#include "body.h"
#include "../id_generator.h"
#include <Box2D/Dynamics/b2Body.h>

Body::Body(b2World &world, float32 xPos, float32 yPos):
           id(IdGenerator::getNewId()), updated(false), lastPosition(xPos, yPos), world(world), body() {}

bool Body::changedPosition() {
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

Body::~Body() = default;
