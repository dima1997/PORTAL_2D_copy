//
// Created by franciscosicardi on 20/06/19.
//

#ifndef PORTAL_ENERGY_BALL_H
#define PORTAL_ENERGY_BALL_H


#include "body.h"
#include "energy_emitter.h"

class EnergyBall: public Body {
private:
    b2Vec2 direction;
    EnergyEmitter &emitter;
    void createBody(float32 xPos, float32 yPos) override;
public:
    EnergyBall(b2World &world, float32 xPos, float32 yPos, uint32_t id, EnergyEmitter &emitter);
    ~EnergyBall() override;
    body_type_t getBodyType() override;
};


#endif //PORTAL_ENERGY_BALL_H
