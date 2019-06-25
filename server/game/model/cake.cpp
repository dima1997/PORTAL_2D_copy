//
// Created by franciscosicardi on 03/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "cake.h"

Cake::Cake(b2World &world, float32 xPos, float32 yPos, uint32_t id) : Body(world, xPos, yPos, id), reachedNumber(0) {
    customizeBody();
}

body_type_t Cake::getBodyType() {
    return CAKE;
}

void Cake::customizeBody() {
    body->SetUserData(this);

    b2PolygonShape box;
    box.SetAsBox(0.2f, 0.2f);

    body->CreateFixture(&box, 0.0f);
}

void Cake::reach() {
    ++reachedNumber;
}

Cake::Cake(const Cake &other): Body(other) {}

Cake::~Cake() = default;


