//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_BODY_H
#define PORTAL_BODY_H


#include <cstdint>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>

class Body {
private:
    uint32_t id;
    bool updated;
    b2Vec2 lastPosition;
    virtual void createBody(float32 xPos, float32 yPos) = 0;
protected:
    b2World &world;
    b2Body *body;
public:
    Body(b2World &world, float32 xPos, float32 yPos);
    virtual ~Body();
    bool changedPosition();
    uint32_t getId();
    float32 getXPos();
    float32 getYPos();
};


#endif //PORTAL_BODY_H
