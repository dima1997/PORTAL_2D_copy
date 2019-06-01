//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H


#include "body.h"

class Chell: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
    uint32_t playerId;
    void move(float32 xSpeed, float32 ySpeed);
public:
    Chell(b2World &world, float32 xPos, float32 yPos, uint32_t playerId);
    uint32_t getPlayerId();
    ~Chell() override;
    void moveLeft();
    void moveRight();
    void jump();
};


#endif //PORTAL_CHELL_H
