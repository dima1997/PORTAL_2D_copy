//
// Created by franciscosicardi on 20/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "energy_emitter.h"

EnergyEmitter::EnergyEmitter(b2World &world, float32 xPos, float32 yPos, uint32_t id, direction_t direction):
                             Body(world, xPos, yPos, id), direction(direction) {
    createBody(xPos, yPos);
}

void EnergyEmitter::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    body = world.CreateBody(&bodyDef);
    body->SetUserData(this);
    b2PolygonShape box;
    box.SetAsBox(0.5f, 0.5f);
    hx = 0.5f;
    hy = 0.5f;
    body->CreateFixture(&box, 0.0f);
}

body_type_t EnergyEmitter::getBodyType() {
    return ENERGY_EMITTER;
}

b2Vec2 EnergyEmitter::getDeparturePos() {
    b2Vec2 add;
    switch (direction) {
        case LEFT_D:
            add = b2Vec2(-hx, 0);
            break;
        case UP_D:
            add = b2Vec2(0, hy);
            break;
        case DOWN_D:
            add = b2Vec2(0, -hy);
            break;
        case RIGHT_D:
            add = b2Vec2(hx, 0);
            break;
    }
    return body->GetPosition() + add;
}

direction_t EnergyEmitter::getDirection() {
    return direction;
}

EnergyEmitter::~EnergyEmitter() = default;
