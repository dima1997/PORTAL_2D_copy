//
// Created by franciscosicardi on 17/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "barrier.h"

Barrier::Barrier(b2World &world, float32 xPos, float32 yPos, uint32_t id, float32 hy, float32 hx):
                 Body(world, xPos, yPos, id) {
    this->hx = hx;
    this->hy = hy;
    customizeBody();
}

body_type_t Barrier::getBodyType() {
    return BARRIER;
}

void Barrier::customizeBody() {
    b2PolygonShape box;
    box.SetAsBox(hx, hy);
    b2FixtureDef sensorFixtureDef;
    sensorFixtureDef.shape = &box;
    sensorFixtureDef.isSensor = true;
    body->CreateFixture(&sensorFixtureDef);
}

Barrier::Barrier(const Barrier &other): Body(other) {
    this->hx = other.hx;
    this->hy = other.hy;
}

Barrier::~Barrier() = default;
