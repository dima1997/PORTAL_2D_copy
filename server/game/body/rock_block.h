//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_ROCK_BLOCK_H
#define PORTAL_ROCK_BLOCK_H


#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include "body.h"

class RockBlock: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
public:
    RockBlock(b2World &world, float32 xPos, float32 yPos, uint32_t id);
    ~RockBlock() override;
};


#endif //PORTAL_ROCK_BLOCK_H
