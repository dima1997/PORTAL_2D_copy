//
// Created by franciscosicardi on 22/06/19.
//

#ifndef PORTAL_ENERGY_RECEIVER_H
#define PORTAL_ENERGY_RECEIVER_H


#include <list>
#include "body.h"
#include "door.h"
#include "switchable.h"

class EnergyReceiver: public Body, public Switchable {
private:
    void customizeBody() override;
    std::list<std::reference_wrapper<Door>> doors;
    void _switchState() override;
public:
    EnergyReceiver(b2World &world, float32 xPos, float32 yPos, uint32_t id, std::list<std::reference_wrapper<Door>> &doors);
    EnergyReceiver(const EnergyReceiver &other);
    ~EnergyReceiver() override;
    body_type_t getBodyType() override;

};


#endif //PORTAL_ENERGY_RECEIVER_H
