//
// Created by franciscosicardi on 03/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "cake.h"

Cake::Cake(b2World &world, float32 xPos, float32 yPos, uint32_t id) : Body(world, xPos, yPos, id), reached(false) {
    createBody(xPos, yPos);
}

body_type_t Cake::getBodyType() {
    return CAKE;
}

void Cake::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    body = world.CreateBody(&bodyDef);
    body->SetUserData(this);

    b2PolygonShape box;
    box.SetAsBox(0.2f, 0.2f);

    body->CreateFixture(&box, 0.0f)->SetSensor(true);
}

void Cake::reach() {
    reached = true;
}

bool Cake::wasReached() {
    return reached;
}

Cake::Cake(const Cake &other): Body(other), reached(other.reached) {}

Cake::~Cake() = default;


