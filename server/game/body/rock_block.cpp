//
// Created by franciscosicardi on 25/05/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "rock_block.h"

RockBlock::RockBlock(b2World &world, float32 xPos, float32 yPos):
           Body(world, xPos, yPos) {
    createBody(xPos, yPos);
}

//RockBlock::~RockBlock() {
//    world.DestroyBody(body);
//}
RockBlock::~RockBlock() = default;

void RockBlock::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    body = world.CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(0.5f, 0.5f);

    body->CreateFixture(&box, 0.0f);
}
