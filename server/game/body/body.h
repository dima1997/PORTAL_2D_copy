//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_BODY_H
#define PORTAL_BODY_H


#include <cstdint>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>

class Body {
private:
    bool updated;
    b2Vec2 lastPosition;
    virtual void createBody(float32 xPos, float32 yPos) = 0;
protected:
    uint32_t id;
    b2World &world;
    b2Body *body;
public:
    Body(b2World &world, float32 xPos, float32 yPos, uint32_t id);
    virtual ~Body();
    bool changedPosition();
    uint32_t getId();
    float32 getXPos();
    float32 getYPos();
};


#endif //PORTAL_BODY_H
