//
// Created by franciscosicardi on 10/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "rock.h"

Rock::Rock(b2World &world, float32 xPos, float32 yPos, uint32_t id, float32 hx, float32 hy):
           Body(world, xPos, yPos, id), initialX(xPos), initialY(yPos) {
    this->hx = hx;
    this->hy = hy;
    createBody(xPos, yPos);
}

Rock::Rock(Rock &&other) noexcept: Body(std::move(other)), initialX(other.initialX), initialY(other.initialY) {}

body_type_t Rock::getBodyType() {
    return ROCK;
}

void Rock::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    body = world.CreateBody(&bodyDef);
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
