//
// Created by franciscosicardi on 25/05/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "block.h"

Block::Block(b2World &world, float32 xPos, float32 yPos, block_type_t type, uint32_t id):
           Body(world, xPos, yPos, id), type(type) {
    createBody(xPos, yPos);
}

//Block::Block
//    world.DestroyBody(body);
//}
Block::~Block() = default;

void Block::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    body = world.CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(0.5f, 0.5f);

    body->CreateFixture(&box, 0.0f);
}
