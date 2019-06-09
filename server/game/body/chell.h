//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H


#include <Box2D/Common/b2Timer.h>
#include "body.h"
#include "portal.h"

#define GROUND_CHECK 1

typedef enum chell_state {LEFT, RIGHT, STOP, JUMP, AIR} chell_state_t;
typedef enum portal_color {BLUE, ORANGE} portal_color_t;

class Chell: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
    Portal *portals[2];
    chell_state_t state;
    bool isJumping();
    bool alive;
    b2Timer jumpTimer;
public:
    int footContacts;
    Chell(b2World &world, float32 xPos, float32 yPos, uint32_t playerId, Portal *bluePortal, Portal *orangePortal);
    bool isAlive();
    ~Chell() override;
    void updateState(chell_state_t state);
    void update();
    Portal *getPortal(portal_color_t color);
    body_type_t getBodyType() override;
    void die();
    void shootPortal(float x, float y, portal_color_t color);
};


#endif //PORTAL_CHELL_H
