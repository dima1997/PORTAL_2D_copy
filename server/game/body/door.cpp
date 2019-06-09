//
// Created by franciscosicardi on 09/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "door.h"

Door::Door(b2World &world, float32 xPos, float32 yPos, uint32_t id,
           std::unordered_map<uint32_t, bool> &conditions): Body(world, xPos, yPos, id), conditions(std::move(conditions)), current() {
    for (auto cond : conditions) {
        current.insert(std::make_pair(cond.first, false));
    }
    createBody(xPos, yPos);
}

body_type_t Door::getBodyType() {
    return DOOR;
}

void Door::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    body = world.CreateBody(&bodyDef);
    body->SetUserData(this);

    b2PolygonShape door;
    door.SetAsBox(0.4f, 1.0f);

    body->CreateFixture(&door, 0.0f);
}

Door::~Door() = default;
