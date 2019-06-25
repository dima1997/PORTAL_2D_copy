//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H


#include <Box2D/Common/b2Timer.h>
#include "movable_body.h"
#include "portal.h"
#include "rock.h"
#include "pin_tool.h"


typedef enum chell_state {LEFT, RIGHT, STOP, JUMP, AIR} chell_state_t;
typedef enum portal_color {BLUE, ORANGE} portal_color_t;
typedef enum rock_state {THROW_RIGHT, THROW_LEFT, THROW_IN, THROW_INITIAL, NO_ROCK, HAS_ROCK} rock_state_t;

class Chell: public MovableBody {
private:
    void customizeBody() override;
    Portal portals[2];
    PinTool pinTool;
    chell_state_t state;
    bool isJumping();
    bool _justDied;
    b2Timer jumpTimer;
    float32 maxReach;
    bool rockStateUpdated;
    bool threwRockUpdated;
    rock_state_t rockState;
    Rock *rock;
    bool grabIfRock(Body *body);
    bool _changedPosition() override;
    void update();
public:
    int footContacts;
    bool throughPortal;
    Chell(b2World &world, float32 xPos, float32 yPos, uint32_t playerId, Portal &bluePortal, Portal &orangePortal,
          PinTool &pinTool, float32 maxReach);
    Chell(const Chell &other);
    ~Chell() override;
    void updateState(chell_state_t state);
    Portal &getPortal(portal_color_t color);
    body_type_t getBodyType() override;
    void die();
    bool justDied();
    void shootPortal(float x, float y, portal_color_t color);
    void grabRock();
    void throwRock(rock_state_t state);
    bool grabbedRock();
    bool threwRock();
    Rock &getRock();
    void resetPortals();
    void showPinTool(float32 x, float32 y);
    PinTool &getPinTool();
};


#endif //PORTAL_CHELL_H
