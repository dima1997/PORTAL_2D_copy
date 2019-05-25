//
// Created by franciscosicardi on 19/05/19.
//

#include <cstdio>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "world.h"

#define TIME_STEP 1.0f / 60.0f
#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 2

World::World(uint8_t map_id): gravity(0.0f, -9.8f), world(new b2World(gravity)) {
    loadMap(map_id);
}

void World::step(std::list<b2Body *> &updated) {

    float32 timeStep = TIME_STEP;

    int32 velocityIterations = VELOCITY_ITERATIONS;
    int32 positionIterations = POSITION_ITERATIONS;

    world->Step(timeStep, velocityIterations, positionIterations);

    for(b2Body *body = world->GetBodyList(); body != nullptr; body = body->GetNext()) {
        updated.push_back(body);
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

