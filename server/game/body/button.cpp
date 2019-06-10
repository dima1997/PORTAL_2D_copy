//
// Created by franciscosicardi on 09/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "button.h"

Button::Button(b2World &world, float32 xPos, float32 yPos, uint32_t id, std::list<Door *> &doors):
               Body(world, xPos, yPos, id), doors(doors), contactCount(0) {
    createBody(xPos, yPos);
}

body_type_t Button::getBodyType() {
    return BUTTON;
}

void Button::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    body = world.CreateBody(&bodyDef);
    body->SetUserData(this);

    b2PolygonShape button;
    button.SetAsBox(0.60f, 0.10f);

    body->CreateFixture(&button, 0.0f);

    b2CircleShape circleShape;
    circleShape.m_radius = 0.10f;

    circleShape.m_p.Set(-0.70, -0.10f);
    body->CreateFixture(&circleShape, 0.0f);
    circleShape.m_p.Set(0.70, -0.10f);
    body->CreateFixture(&circleShape, 0.0f);

    b2PolygonShape sensorShape;
    sensorShape.SetAsBox(0.50f, 0.09f, b2Vec2(0.0f, 0.025f), 0.0f);
    b2FixtureDef sensorFixtureDef;
    sensorFixtureDef.shape = &sensorShape;
    sensorFixtureDef.isSensor = true;
    sensorFixtureDef.userData = (void *)CONTACT_CHECK;

    body->CreateFixture(&sensorFixtureDef);
}

void Button::updateDoors(bool status) {
    for (auto &door : doors) {
        door->updateConditionStatus(this->id, status);
    }
}

void Button::increaseContact() {
    ++contactCount;
    if (contactCount == 1) {
        updateDoors(true);
    }
}

void Button::decreaseContact() {
    --contactCount;
    if (contactCount == 0) {
        updateDoors(false);
    }
}

Button::~Button() = default;
