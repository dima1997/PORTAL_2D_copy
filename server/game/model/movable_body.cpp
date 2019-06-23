//
// Created by franciscosicardi on 25/05/19.
//

#include "movable_body.h"

MovableBody::MovableBody(b2World &world, float32 xPos, float32 yPos, uint32_t id): Body(world, xPos, yPos, id),
                         updated_position(false) {
    body->SetType(b2_dynamicBody);
}

bool MovableBody::changedPosition() {
    if (updated_position) {
        _moveTo(lastPosition.x, lastPosition.y);
        updated_position = false;
        return true;
    }
    return _changedPosition();
}

void MovableBody::applyImpulse(float32 xSpeed, float32 ySpeed) {
    b2Vec2 vel = body->GetLinearVelocity();
    float32 dvx = xSpeed - vel.x;
    float32 dvy = ySpeed - vel.y;
    float32 mass = body->GetMass();
    body->ApplyLinearImpulseToCenter(b2Vec2(mass * dvx, mass * dvy), true);
}

void MovableBody::moveTo(float32 x, float32 y) {
    lastPosition = b2Vec2(x, y);
    updated_position = true;
}

b2Vec2 MovableBody::getCurrentVelocity() {
    return body->GetLinearVelocity();
}

MovableBody::MovableBody(const MovableBody &other): Body(other), updated_position(other.updated_position) {}

void MovableBody::_moveTo(float32 x, float32 y) {
        body->SetTransform(lastPosition, body->GetAngle());
}

bool MovableBody::_changedPosition() {
    if (lastPosition != body->GetPosition()) {
        lastPosition = body->GetPosition();
        return true;
    }
    return false;
}

MovableBody::~MovableBody() = default;
