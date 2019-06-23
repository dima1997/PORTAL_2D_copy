//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_BODY_H
#define PORTAL_BODY_H


#include <cstdint>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>

#define CONTACT_CHECK 1

typedef enum body_type {ROCK_BLOCK, METAL_BLOCK, ACID_BLOCK, CHELL, PORTAL, CAKE, DOOR, BUTTON, ROCK, BARRIER, ENERGY_EMITTER, ENERGY_RECEIVER, ENERGY_BALL, PIN_TOOL} body_type_t;
bool is_movable(body_type_t bodyType);

class Body {
private:
    virtual void customizeBody();
protected:
    uint32_t id;
    b2World &world;
    b2Body *body;
    b2Vec2 lastPosition;
public:
    Body(b2World &world, float32 xPos, float32 yPos, uint32_t id);
    Body(const Body &other);
    virtual ~Body();
    float32 hx;
    float32 hy;
    uint32_t getId();
    float32 getXPos();
    float32 getYPos();
    virtual body_type_t getBodyType() = 0;
};


#endif //PORTAL_BODY_H
