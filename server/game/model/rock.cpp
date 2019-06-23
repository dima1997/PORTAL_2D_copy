//
// Created by franciscosicardi on 10/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "rock.h"

Rock::Rock(b2World &world, float32 xPos, float32 yPos, uint32_t id, float32 hx, float32 hy):
           MovableBody(world, xPos, yPos, id), initialX(xPos), initialY(yPos) {
    this->hx = hx;
    this->hy = hy;
    customizeBody();
}

Rock::Rock(const Rock &other): MovableBody(other), initialX(other.initialX), initialY(other.initialY) {}

body_type_t Rock::getBodyType() {
    return ROCK;
}

void Rock::customizeBody() {
    body->SetUserData(this);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(hx, hy);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 0.4f / (hx * hy);
    fixtureDef.friction = 2.0f;

    body->CreateFixture(&fixtureDef);
}

void Rock::setActive(bool active) {
    body->SetActive(active);
}

void Rock::moveToInitial() {
    moveTo(initialX, initialY);
}

Rock::~Rock() = default;
