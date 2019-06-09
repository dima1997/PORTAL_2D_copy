//
// Created by franciscosicardi on 09/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include "button.h"

Button::Button(b2World &world, float32 xPos, float32 yPos, uint32_t id, std::list<Door *> &doors):
               Body(world, xPos, yPos, id), doors(doors) {
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
}

Button::~Button() = default;
