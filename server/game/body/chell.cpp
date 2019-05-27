//
// Created by franciscosicardi on 25/05/19.
//

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "chell.h"

void Chell::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(xPos, yPos);
    body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.5f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

Chell::Chell(b2World &world, float32 xPos, float32 yPos, uint8_t playerId):
             Body(world, xPos, yPos), playerId(playerId) {
    createBody(xPos, yPos);
}

Chell::~Chell() {
    world.DestroyBody(body);
}

void Chell::moveLeft() {
    move(-5, 0);
}

void Chell::move(float32 xSpeed, float32 ySpeed) {
    b2Vec2 vel = body->GetLinearVelocity();
    float32 dvx = xSpeed - vel.x;
    float32 dvy = ySpeed - vel.y;
    float32 mass = body->GetMass();
    body->ApplyLinearImpulse(b2Vec2(mass * dvx, mass * dvy), body->GetWorldCenter(), true);
}

void Chell::moveRight() {
    move(5, 0);
}

void Chell::jump() {
    move(0, 5);
}

uint8_t Chell::getPlayerId() {
    return playerId;
}


