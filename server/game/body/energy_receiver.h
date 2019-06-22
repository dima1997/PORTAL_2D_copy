//
// Created by franciscosicardi on 22/06/19.
//

#ifndef PORTAL_ENERGY_RECEIVER_H
#define PORTAL_ENERGY_RECEIVER_H


#include "body.h"

class EnergyReceiver: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
public:
    EnergyReceiver(b2World &world, float32 xPos, float32 yPos, uint32_t id);
    EnergyReceiver(const EnergyReceiver &other);
    ~EnergyReceiver() override;
    body_type_t getBodyType() override;

};


#endif //PORTAL_ENERGY_RECEIVER_H
