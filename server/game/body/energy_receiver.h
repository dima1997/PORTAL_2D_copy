//
// Created by franciscosicardi on 22/06/19.
//

#ifndef PORTAL_ENERGY_RECEIVER_H
#define PORTAL_ENERGY_RECEIVER_H


#include <list>
#include "body.h"
#include "door.h"

class EnergyReceiver: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
    bool active;
    bool updatedActive;
    std::list<std::reference_wrapper<Door>> doors;
    void updateDoors();
public:
    EnergyReceiver(b2World &world, float32 xPos, float32 yPos, uint32_t id, std::list<std::reference_wrapper<Door>> &doors);
    EnergyReceiver(const EnergyReceiver &other);
    ~EnergyReceiver() override;
    body_type_t getBodyType() override;
    void updateActive();
    bool wasUpdated();

};


#endif //PORTAL_ENERGY_RECEIVER_H
