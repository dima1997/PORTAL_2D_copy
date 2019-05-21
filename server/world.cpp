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

void World::step(std::list<b2Body *> &updated) {

    float32 timeStep = TIME_STEP;

    int32 velocityIterations = VELOCITY_ITERATIONS;
    int32 positionIterations = POSITION_ITERATIONS;

    world->Step(timeStep, velocityIterations, positionIterations);
    b2Body *body = world->GetBodyList();
    while(body != nullptr) {
        auto *bodyInfo = (BodyInfo *) body->GetUserData();
        bodyInfo->update(body->GetPosition());
        if (body->IsAwake() && bodyInfo->isUpdated()) {
            updated.push_back(body);
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
    createRockBlock(0, -1.5);
    createChell(0, 4, 0);
}

void World::createRockBlock(float32 x_pos, float32 y_pos) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(x_pos, y_pos);
    auto *bodyInfo = new BodyInfo(bodies.size(), bodyDef.position);
    bodyDef.userData = bodyInfo;
    b2Body *body = world->CreateBody(&bodyDef);
    bodies.push_back(body);

    b2PolygonShape box;
    box.SetAsBox(1.5f, 1.5f);

    body->CreateFixture(&box, 0.0f);
}

void World::createChell(float32 x_pos, float32 y_pos, uint8_t playerId) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x_pos, y_pos);
    auto *bodyInfo = new BodyInfo(bodies.size(), bodyDef.position);
    bodyDef.userData = bodyInfo;
    b2Body *body = world->CreateBody(&bodyDef);
    bodies.push_back(body);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.5f, 0.5f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}
