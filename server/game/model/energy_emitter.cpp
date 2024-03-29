//
// Created by franciscosicardi on 20/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "energy_emitter.h"

EnergyEmitter::EnergyEmitter(b2World &world, float32 xPos, float32 yPos, uint32_t id, direction_t direction):
                             Body(world, xPos, yPos, id), direction(direction) {
    customizeBody();
}

EnergyEmitter::EnergyEmitter(const EnergyEmitter &other): Body(other), direction(other.direction) {}

void EnergyEmitter::customizeBody() {
    b2PolygonShape box;
    box.SetAsBox(0.5f, 0.5f);
    hx = 0.5f;
    hy = 0.5f;
    body->CreateFixture(&box, 0.0f);
}

body_type_t EnergyEmitter::getBodyType() {
    return ENERGY_EMITTER;
}

direction_t EnergyEmitter::getDirection() {
    return direction;
}

EnergyEmitter::~EnergyEmitter() = default;
