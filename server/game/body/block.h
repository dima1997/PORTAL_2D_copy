//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_BLOCK_H
#define PORTAL_BLOCK_H


#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include "body.h"

typedef enum block_type {ROCK, METAL, ACID} block_type_t;

class Block: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
    block_type_t type;
public:
    Block(b2World &world, float32 xPos, float32 yPos, block_type_t type, uint32_t id);
    ~Block() override;
    body_type_t getBodyType() override;
};


#endif //PORTAL_BLOCK_H
