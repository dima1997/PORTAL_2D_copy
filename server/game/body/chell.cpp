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
    dynamicBox.SetAsBox(0.5f, 0.75f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

Chell::Chell(b2World &world, float32 xPos, float32 yPos, uint32_t playerId):
             Body(world, xPos, yPos), playerId(playerId) {
    createBody(xPos, yPos);
}

//Chell::~Chell() {
//    world.DestroyBody(body);
//}
Chell::~Chell() = default;

void Chell::moveLeft() {
    move(-3.0f, 0.0f); // -2.0
}

void Chell::move(float32 xSpeed, float32 ySpeed) {
    b2Vec2 vel = body->GetLinearVelocity();
    float32 dvx = xSpeed - vel.x;
    float32 dvy = ySpeed - vel.y;
    float32 mass = body->GetMass();
    printf("move: %f, %f\n", dvx, dvy);
    body->ApplyLinearImpulse(b2Vec2(mass * dvx, mass * dvy), body->GetWorldCenter(), true);
}

void Chell::moveRight() {
    move(3.0f, 0.0f); // cambiado a 5.0f, antes era 1.0f (by Dima)
}

void Chell::jump() {
    b2Vec2 vel = body->GetLinearVelocity();
    if (vel.y == 0) {
        move(0.0f, 7.0f); // 0.5f
    }
}

uint32_t Chell::getPlayerId() {
    return playerId;
}


