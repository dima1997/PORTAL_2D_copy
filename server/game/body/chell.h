//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H


#include "body.h"
#include "portal.h"

typedef enum chell_state {LEFT, RIGHT, STOP} chell_state_t;
typedef enum portal_color {BLUE, ORANGE} portal_color_t;

class Chell: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
    Portal *portals[2];
    chell_state_t state;
    bool jump_state;
    bool isJumping();
    bool alive;
public:
    Chell(b2World &world, float32 xPos, float32 yPos, uint32_t playerId, Portal *bluePortal, Portal *orangePortal);
    bool isAlive();
    ~Chell() override;
    void jump();
    void updateState(chell_state_t state);
    void update();
    Portal *getPortal(portal_color_t color);
    body_type_t getBodyType() override;
    void die();
    void shootPortal(float x, float y, portal_color_t color);
};


#endif //PORTAL_CHELL_H
