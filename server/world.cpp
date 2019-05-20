//
// Created by franciscosicardi on 19/05/19.
//

#include <cstdio>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "world.h"

#define TIME_STEP 1.0f / 60.0f
#define VELOCITY_ITERATIONS 8;
#define POSITION_ITERATIONS 2;

World::World(uint8_t map_id): gravity(0.0f, -9.8f), world(new b2World(gravity)) {
    loadMap(map_id);
}

void World::step(std::list<Body *> &updated) {

    float32 timeStep = TIME_STEP;

    int32 velocityIterations = VELOCITY_ITERATIONS;
    int32 positionIterations = POSITION_ITERATIONS;

    world->Step(timeStep, velocityIterations, positionIterations);
    b2Body *body = world->GetBodyList();
    while(body != nullptr) {
        b2Vec2 position = body->GetPosition();
        if (body->IsAwake()) {
            printf("x: %4.2f, y: %4.2f\n", position.x, position.y);
        }
        body = body->GetNext();
    }
}

World::World(World &&other) noexcept: gravity(other.gravity), world(other.world) {
    other.world = nullptr;
}

World &World::operator=(World &&other) noexcept {
    this->gravity = other.gravity;
    this->world = other.world;
    other.world = nullptr;
    return *this;
}

World::~World() {
    delete world;
}

void World::loadMap(uint8_t mapId) {
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body * groundBody = world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef elementBodyDef;
    elementBodyDef.position.Set(-1.3f, 1.0f);
    b2Body * elementBody = world->CreateBody(&elementBodyDef);

    b2PolygonShape elementBox;
    elementBox.SetAsBox(1.0f, 1.0f);

    elementBody->CreateFixture(&elementBox, 0.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body *body = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}
