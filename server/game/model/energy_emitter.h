//
// Created by franciscosicardi on 20/06/19.
//

#ifndef PORTAL_ENERGY_EMITTER_H
#define PORTAL_ENERGY_EMITTER_H


#include "body.h"

typedef enum direction {UP_D, DOWN_D, RIGHT_D, LEFT_D} direction_t;

class EnergyEmitter: public Body {
private:
    direction_t direction;
    void customizeBody() override;
public:
    EnergyEmitter(b2World &world, float32 xPos, float32 yPos, uint32_t id, direction_t direction);
    EnergyEmitter(const EnergyEmitter &other);
    ~EnergyEmitter() override;
    body_type_t getBodyType() override;
    direction_t getDirection();
};


#endif //PORTAL_ENERGY_EMITTER_H
