//
// Created by franciscosicardi on 19/05/19.
//

#include <cstdio>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "world.h"
#include "body/block.h"

#include <configs_yaml/config_paths.h>
#include <portal_exception.h>
#include "yaml-cpp/yaml.h"
#include "contact_listeners/portal_contact_listener.h"

#define TIME_STEP 1.0f / 60.0f
#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 2

World::World(Map &map): gravity(0.0f, -9.8f), world(new b2World(gravity)),
                              chells(), staticBodies(), numberOfPlayers() {
    loadMap(map);
    std::unique_ptr<PortalContactListener> portalContactListener(new PortalContactListener());
    world->SetContactListener(portalContactListener.get());
    listeners.push_back(std::move(portalContactListener));
}

void World::step(std::list<std::shared_ptr<ObjectMovesEvent>> &moved) {

    float32 timeStep = TIME_STEP;

    int32 velocityIterations = VELOCITY_ITERATIONS;
    int32 positionIterations = POSITION_ITERATIONS;

    for(Chell *chell : chells) {
        chell->update();
    }

    world->Step(timeStep, velocityIterations, positionIterations);

    for(Chell *chell : chells) {
        if(chell->changedPosition()) {
            moved.push_back(std::shared_ptr<ObjectMovesEvent>(new ObjectMovesEvent(chell->getId(), chell->getXPos(), chell->getYPos())));
        }
        Portal *orange = chell->getOrangePortal();
        if(orange->changedPosition()) {
            moved.push_back(std::shared_ptr<ObjectMovesEvent>(new ObjectMovesEvent(orange->getId(), orange->getXPos(), orange->getYPos())));
        }
        Portal *blue = chell->getBluePortal();
        if(blue->changedPosition()) {
            moved.push_back(std::shared_ptr<ObjectMovesEvent>(new ObjectMovesEvent(blue->getId(), blue->getXPos(), blue->getYPos())));
        }
    }

}

//World::World(World &&other) noexcept: gravity(other.gravity), world(other.world), chells(std::move(other.chells)),
//                                      staticBodies(std::move(other.staticBodies)), numberOfPlayers(other.numberOfPlayers) {
//    other.world = nullptr;
//}

//World &World::operator=(World &&other) noexcept {
//    this->gravity = other.gravity;
//    this->world = other.world;
//    other.world = nullptr;
//    this->staticBodies = std::move(other.staticBodies);
//    this->chells = std::move(other.chells);
//    return *this;
//}

World::~World() {
    for (auto *chell : chells) {
        delete chell;
    }
    for(auto *body : staticBodies) {
        delete body;
    }
    delete world;
}

void World::loadMap(Map &map) {
    // TODO: this should be Map's responsability
    YAML::Node baseNode = map.getFile();
    YAML::Node blocks = baseNode["blocks"];
    float widthBlock = blocks["width"].as<float>(); // TODO : Actualizar codigo para utilizar estos tamanios del YAML
    float heightBlock = blocks["height"].as<float>(); //  Puedes usar float32 si gustas
    YAML::Node blocksIdCoords = blocks["id_material_coordinates"];
    for(int i = 0; i < (int)blocksIdCoords.size(); ++i) {
        uint32_t id = blocksIdCoords[i]["id"].as<uint32_t>();
        std::string material = blocksIdCoords[i]["material"].as<std::string>();
        float32 x = blocksIdCoords[i]["xCoord"].as<float32>();
        float32 y = blocksIdCoords[i]["yCoord"].as<float32>();
        if (material == "rock") {
            staticBodies.push_back(new Block(*world, x, y, ROCK, id));
        } else if (material == "metal") {
            staticBodies.push_back(new Block(*world, x, y, METAL, id));
        } else if (material == "acid") {
            staticBodies.push_back(new Block(*world, x, y, ACID, id));
        }
    }
    YAML::Node chellsYaml = baseNode["chells"];
    float widthChell = chellsYaml["width"].as<float>(); 
    float heightChell = chellsYaml["height"].as<float>(); 
    YAML::Node chellsIdCoords = chellsYaml["id_coordinates"];
    for (int i = 0; i < (int)chellsIdCoords.size(); ++i){
        uint32_t id = chellsIdCoords[i]["id"].as<uint32_t>();  
        float32 x = chellsIdCoords[i]["xCoord"].as<float32>();
        float32 y = chellsIdCoords[i]["yCoord"].as<float32>();
        chells.push_back(new Chell(*world, x, y, id)); 
    }
    YAML::Node portalsYaml = baseNode["portals"];
    float portalWidth = portalsYaml["width"].as<float>(); 
    float portalHeight = portalsYaml["height"].as<float>(); 
    YAML::Node portalsIdColorCoords = portalsYaml["id_color_coordinates"];
    std::vector<Portal *> portals;
    for (int i = 0; i < (int)portalsIdColorCoords.size(); ++i){
        uint32_t id = portalsIdColorCoords[i]["id"].as<uint32_t>();
        std::string color = portalsIdColorCoords[i]["color"].as<std::string>();  
        float32 x = portalsIdColorCoords[i]["xCoord"].as<float32>();
        float32 y = portalsIdColorCoords[i]["yCoord"].as<float32>();
        portals.push_back(new Portal(*world, x, y, id));
        // Aqui se agregan los portales
    }
    int i = 0;
    for(auto chell : chells) {
        chell->setBluePortal(portals[i++]);
        chell->setOrangePortal(portals[i++]);
        connect(portals[i - 1], portals[i - 2]);
    }
    numberOfPlayers = map.getPlayersNumber();
}

Chell *World::getChell(uint32_t i) {
    for (auto *chell : chells) {
        if (chell->getId() == i) {
            return chell;
        }
    }
    std::stringstream s;
    s << "Inexistent Chell with id " << i;
    throw PortalException(s.str());
}

// Modificar a gusto.

// Agregado por Dima --------------------