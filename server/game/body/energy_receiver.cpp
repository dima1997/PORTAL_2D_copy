//
// Created by franciscosicardi on 22/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "energy_receiver.h"

void EnergyReceiver::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    body = world.CreateBody(&bodyDef);
    body->SetUserData(this);
    b2PolygonShape box;
    box.SetAsBox(0.5f, 0.5f);
    hx = 0.5f;
    hy = 0.5f;
    body->CreateFixture(&box, 0.0f);
}

EnergyReceiver::EnergyReceiver(b2World &world, float32 xPos, float32 yPos, uint32_t id):
                               Body(world, xPos, yPos, id), updatedActive(false) {
    createBody(xPos, yPos);
}

EnergyReceiver::EnergyReceiver(const EnergyReceiver &other): Body(other), updatedActive(other.updatedActive) {}

body_type_t EnergyReceiver::getBodyType() {
    return ENERGY_RECEIVER;
}

bool EnergyReceiver::wasUpdated() {
    bool updated = updatedActive;
    updatedActive = false;
    return updated;
}

void EnergyReceiver::updateActive() {
    updatedActive = true;
}

EnergyReceiver::~EnergyReceiver() = default;
