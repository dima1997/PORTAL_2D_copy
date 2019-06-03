//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H


#include "body.h"
#include "portal.h"

typedef enum chell_state {LEFT, RIGHT, STOP} chell_state_t;

class Chell: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
    void move(float32 xSpeed, float32 ySpeed);
    Portal *orangePortal;
    Portal *bluePortal;
    chell_state_t state;
    bool jump_state;
    bool isJumping();
public:
    Chell(b2World &world, float32 xPos, float32 yPos, uint32_t playerId);
    void setOrangePortal(Portal *portal);
    void setBluePortal(Portal *portal);
    ~Chell() override;
    void jump();
    void updateState(chell_state_t state);
    void update();
    void moveBluePortal(float d, float d1);
    void moveOrangePortal(float32 x, float32 y);
    Portal *getOrangePortal();
    Portal *getBluePortal();
    body_type_t getBodyType() override;
};


#endif //PORTAL_CHELL_H
