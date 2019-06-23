//
// Created by franciscosicardi on 22/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "energy_receiver.h"
#include "door.h"

void EnergyReceiver::customizeBody() {
    b2PolygonShape box;
    box.SetAsBox(0.5f, 0.5f);
    hx = 0.5f;
    hy = 0.5f;
    body->CreateFixture(&box, 0.0f);
}

EnergyReceiver::EnergyReceiver(b2World &world, float32 xPos, float32 yPos, uint32_t id, std::list<std::reference_wrapper<Door>> &doors):
                               Body(world, xPos, yPos, id), Switchable(), doors(doors) {
    customizeBody();
}

EnergyReceiver::EnergyReceiver(const EnergyReceiver &other): Body(other), Switchable(other), doors(other.doors) {}

body_type_t EnergyReceiver::getBodyType() {
    return ENERGY_RECEIVER;
}

void EnergyReceiver::_switchState() {
    for (auto &door : doors) {
        door.get().updateConditionStatus(this->id);
    }
}

EnergyReceiver::~EnergyReceiver() = default;
