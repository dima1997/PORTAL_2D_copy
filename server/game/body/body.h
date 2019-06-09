//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_BODY_H
#define PORTAL_BODY_H


#include <cstdint>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>

typedef enum body_type {ROCK_BLOCK, METAL_BLOCK, ACID_BLOCK, CHELL, PORTAL, CAKE, DOOR, BUTTON} body_type_t;

class Body {
private:
    bool updated_position;
    b2Vec2 lastPosition;
    virtual void createBody(float32 xPos, float32 yPos) = 0;
protected:
    uint32_t id;
    b2World &world;
    b2Body *body;
public:
    Body(b2World &world, float32 xPos, float32 yPos, uint32_t id);
    virtual ~Body();
    bool throughPortal;
    float32 hx;
    float32 hy;
    void applyImpulse(float32 xSpeed, float32 ySpeed);
    bool changedPositionOrVelocity();
    uint32_t getId();
    float32 getXPos();
    float32 getYPos();
    void moveTo(float32 x, float32 y);
    b2Vec2 getCurrentVelocity();
    virtual body_type_t getBodyType() = 0;
};


#endif //PORTAL_BODY_H
