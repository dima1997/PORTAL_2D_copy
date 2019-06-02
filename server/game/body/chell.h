//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H


#include "body.h"

typedef enum chell_state {LEFT, RIGHT, STOP} chell_state_t;

class Chell: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
    void move(float32 xSpeed, float32 ySpeed);
    chell_state_t state;
    bool jump_state;
    bool isNotJumping();
public:
    Chell(b2World &world, float32 xPos, float32 yPos, uint32_t playerId);
    ~Chell() override;
    void jump();
    void updateState(chell_state_t state);
    void update();
};


#endif //PORTAL_CHELL_H
