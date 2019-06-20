//
// Created by franciscosicardi on 20/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "energy_emitter.h"

EnergyEmitter::EnergyEmitter(b2World &world, float32 xPos, float32 yPos, uint32_t id, direction_t direction):
                             Body(world, xPos, yPos, id), direction(direction) {
    createBody(xPos, yPos);
}

void EnergyEmitter::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    body = world.CreateBody(&bodyDef);
    body->SetUserData(this);
    b2PolygonShape box;
    box.SetAsBox(0.5f, 0.5f);
    body->CreateFixture(&box, 0.0f);
}

body_type_t EnergyEmitter::getBodyType() {
    return ENERGY_EMITTER;
}

EnergyEmitter::~EnergyEmitter() = default;
