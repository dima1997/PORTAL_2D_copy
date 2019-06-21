//
// Created by franciscosicardi on 25/05/19.
//

#include "body.h"

Body::Body(b2World &world, float32 xPos, float32 yPos, uint32_t id):
           updated_position(false), lastPosition(xPos, yPos), id(id), world(world), body(), throughPortal(false), hx(), hy() {}

bool Body::changedPosition() {
    if (updated_position) {
        body->SetTransform(lastPosition, body->GetAngle());
        updated_position = false;
        return true;
    }
    if (lastPosition.x != body->GetPosition().x || lastPosition.y != body->GetPosition().y) {
        lastPosition = body->GetPosition();
        return true;
    }
    return false;
}

void Body::applyImpulse(float32 xSpeed, float32 ySpeed) {
    b2Vec2 vel = body->GetLinearVelocity();
    float32 dvx = xSpeed - vel.x;
    float32 dvy = ySpeed - vel.y;
    float32 mass = body->GetMass();
    body->ApplyLinearImpulseToCenter(b2Vec2(mass * dvx, mass * dvy), true);
}

uint32_t Body::getId() {
    return id;
}

float32 Body::getXPos() {
    return lastPosition.x;
}

float32 Body::getYPos() {
    return lastPosition.y;
}

void Body::moveTo(float32 x, float32 y) {
    lastPosition = b2Vec2(x, y);
    updated_position = true;
}

b2Vec2 Body::getCurrentVelocity() {
    return body->GetLinearVelocity();
}

Body::~Body() = default;
