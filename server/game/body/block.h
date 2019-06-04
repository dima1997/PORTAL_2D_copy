//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_BLOCK_H
#define PORTAL_BLOCK_H


#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include "body.h"

class Block: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
    body_type_t type;
public:
    Block(b2World &world, float32 xPos, float32 yPos, body_type_t type, uint32_t id);
    ~Block() override;
    body_type_t getBodyType() override;
};


#endif //PORTAL_BLOCK_H
