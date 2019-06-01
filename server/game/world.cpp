//
// Created by franciscosicardi on 19/05/19.
//

#include <cstdio>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "world.h"
#include "body/rock_block.h"

#include "config_paths.h"
#include "yaml-cpp/yaml.h"

#define TIME_STEP 1.0f / 60.0f
#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 2

World::World(uint8_t map_id): gravity(0.0f, -9.8f), world(new b2World(gravity)),
                              chells(), staticBodies(), numberOfPlayers() {
    loadMap(map_id);
}

void World::step(std::list<ObjectMovesEvent *> &moved) {

    float32 timeStep = TIME_STEP;

    int32 velocityIterations = VELOCITY_ITERATIONS;
    int32 positionIterations = POSITION_ITERATIONS;

    world->Step(timeStep, velocityIterations, positionIterations);

    for(Chell *chell : chells) {
        if(chell->changedPosition()) {
            moved.push_back(new ObjectMovesEvent(chell->getPlayerId(), chell->getXPos(), chell->getYPos())); //chell->getId()
        }
    }
}

World::World(World &&other) noexcept: gravity(other.gravity), world(other.world), chells(std::move(other.chells)),
                                      staticBodies(std::move(other.staticBodies)), numberOfPlayers(other.numberOfPlayers) {
    other.world = nullptr;
}

World &World::operator=(World &&other) noexcept {
    this->gravity = other.gravity;
    this->world = other.world;
    other.world = nullptr;
    this->staticBodies = std::move(other.staticBodies);
    this->chells = std::move(other.chells);
    return *this;
}

World::~World() {
    for (auto *chell : chells) {
        delete chell;
    }
    for(auto *body : staticBodies) {
        delete body;
    }
    delete world;
}

void World::loadMap(uint8_t mapId) {
    YAML::Node baseNode = YAML::LoadFile(CONFIG_PATHS.at(mapId));
    YAML::Node blocks = baseNode["blocks"];
    float widthBlock = blocks["width"].as<float>(); // TODO : Actualizar codigo para utilizar estos tamanios del YAML
    float heightBlock = blocks["height"].as<float>(); //  Puedes usar float32 si gustas
    YAML::Node blocksIdCoords = blocks["id_coordinates"];
    for(int i = 0; i < (int)blocksIdCoords.size(); ++i) {
        uint32_t id = blocksIdCoords[i]["id"].as<uint32_t>(); // Puedes no usarlo, pero aqui esta. 
        float32 x = blocksIdCoords[i]["xCoord"].as<float32>();
        float32 y = blocksIdCoords[i]["yCoord"].as<float32>();
        staticBodies.push_back(new RockBlock(*world, x, y));
    }
    YAML::Node chellsYaml = baseNode["chells"];
    float widthChell = chellsYaml["width"].as<float>(); 
    float heightChell = chellsYaml["height"].as<float>(); 
    YAML::Node chellsIdCoords = chellsYaml["id_coordinates"];
    for (int i = 0; i < (int)chellsIdCoords.size(); ++i){
        uint32_t id = chellsIdCoords[i]["id"].as<uint32_t>();  
        float32 x = chellsIdCoords[i]["xCoord"].as<float32>();
        float32 y = chellsIdCoords[i]["yCoord"].as<float32>();
        chells.push_back(new Chell(*world, x, y, id)); // Tal vez deberia hardcodearlo a cero.
    }
    YAML::Node portalsYaml = baseNode["portals"];
    float portalWidth = portalsYaml["width"].as<float>(); 
    float portalHeight = portalsYaml["height"].as<float>(); 
    YAML::Node portalsIdColorCoords = portalsYaml["id_color_coordinates"];
    for (int i = 0; i < (int)portalsIdColorCoords.size(); ++i){
        uint32_t id = portalsIdColorCoords[i]["id"].as<uint32_t>();
        std::string color = portalsIdColorCoords[i]["color"].as<std::string>();  
        float32 x = portalsIdColorCoords[i]["xCoord"].as<float32>();
        float32 y = portalsIdColorCoords[i]["yCoord"].as<float32>();
        // Aqui se agregan los portales
    }
    /*
    for(int i = -8; i < 10; ++i) {
        staticBodies.push_back(new RockBlock(*world, (float32) i + 0.5, 0.5));
        staticBodies.push_back(new RockBlock(*world, (float32) i + 0.5, 8.5));
    }
    for(int i = 1; i < 8; ++i) {
        staticBodies.push_back(new RockBlock(*world, 9.5, (float32) i + 0.5));
        staticBodies.push_back(new RockBlock(*world, -7.5, (float32) i + 0.5));
    }
    chells.push_back(new Chell(*world, 0.5f, 1.75f, 0));
    numberOfPlayers = 1;
    */
    numberOfPlayers = 1;
}

int World::getNumberOfPlayers() {
    return numberOfPlayers;
}

void World::moveChellLeft(uint32_t i) {
    for (auto *chell : chells) {
        if (chell->getPlayerId() == i) {
            chell->moveLeft();
            return;
        }
    }
}

void World::moveChellRight(uint32_t i) {
    // TODO: generalize
    for (auto *chell : chells) {
        if (chell->getPlayerId() == i) { 
            chell->moveRight();
            return;
        }
    }
}

// Agregado por Dima --------------------

void World::makeChellJump(uint32_t i) {
    // TODO: generalize
    for (auto *chell : chells) {
        if (chell->getPlayerId() == i) { 
            chell->jump();
            return;
        }
    }
}

// Modificar a gusto.

// Agregado por Dima --------------------