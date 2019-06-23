//
// Created by franciscosicardi on 20/06/19.
//

#ifndef PORTAL_ENERGY_BALL_H
#define PORTAL_ENERGY_BALL_H


#include <Box2D/Common/b2Timer.h>
#include "movable_body.h"
#include "energy_emitter.h"

class EnergyBall: public MovableBody {
private:
    b2Vec2 direction;
    EnergyEmitter &emitter;
    b2Timer timer;
    void resetDirection();
    void customizeBody() override;
public:
    EnergyBall(b2World &world, float32 xPos, float32 yPos, uint32_t id, EnergyEmitter &emitter);
    EnergyBall(const EnergyBall &other);
    ~EnergyBall() override;
    void resetPosition();
    void move();
    body_type_t getBodyType() override;
    void setDirection(b2Vec2 dir);
    b2Vec2 getDirection();
};


#endif //PORTAL_ENERGY_BALL_H
