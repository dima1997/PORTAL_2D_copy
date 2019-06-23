//
// Created by franciscosicardi on 22/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "energy_receiver.h"
#include "door.h"

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

EnergyReceiver::EnergyReceiver(b2World &world, float32 xPos, float32 yPos, uint32_t id, std::list<std::reference_wrapper<Door>> &doors):
                               Body(world, xPos, yPos, id), updatedActive(false), doors(doors) {
    createBody(xPos, yPos);
}

EnergyReceiver::EnergyReceiver(const EnergyReceiver &other): Body(other), updatedActive(other.updatedActive), doors(other.doors) {}

body_type_t EnergyReceiver::getBodyType() {
    return ENERGY_RECEIVER;
}

bool EnergyReceiver::wasUpdated() {
    bool updated = updatedActive;
    updatedActive = false;
    return updated;
}

void EnergyReceiver::updateDoors() {
    updatedActive = true;
    for (auto &door : doors) {
        door.get().updateConditionStatus(this->id);
    }
}

void EnergyReceiver::updateActive() {
    updateDoors();
}

EnergyReceiver::~EnergyReceiver() = default;
