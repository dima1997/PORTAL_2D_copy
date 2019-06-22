//
// Created by franciscosicardi on 02/06/19.
//

#ifndef PORTAL_MAP_H
#define PORTAL_MAP_H


#include <cstdint>
#include <yaml-cpp/node/node.h>
#include "body/cake.h"
#include "body/chell.h"
#include "body/block.h"
#include "body/door.h"
#include "body/button.h"
#include "body/rock.h"
#include "body/barrier.h"
#include "body/energy_emitter.h"
#include "body/energy_ball.h"
#include "body/energy_receiver.h"

class Map {
    YAML::Node file;
    uint8_t id;
    uint8_t players_number;
    Portal loadPortal(const YAML::Node &portal, b2World &world);
    Chell loadChell(const YAML::Node &chell, b2World &world, Portal &bluePortal, Portal &orangePortal);
    Block loadBlock(const YAML::Node &block, b2World &world, body_type_t type, orientation_t orientation);
    EnergyEmitter loadEmitter(const YAML::Node &emitterInfo, b2World &world, direction_t direction);
public:
    explicit Map(uint8_t map_id);
    uint8_t getPlayersNumber();
    uint32_t getPlayerId(uint8_t i);
    Cake loadCake(b2World &world);
    std::list<Block> loadBlocks(b2World &world);
    std::list<Rock> loadRocks(b2World &world);
    std::list<Chell> loadChells(b2World &world);
    std::list<Door> loadDoors(b2World &world);
    std::list<Button> loadButtons(b2World &world, std::list<Door> &doors);
    std::list<Barrier> loadBarriers(b2World &world);
    std::list<EnergyEmitter> loadEmitters(b2World &world);
    std::list<EnergyReceiver> loadReceivers(b2World &world);
    std::list<EnergyBall> loadBalls(b2World &world, std::list<EnergyEmitter> &emmiters);
    std::string toString();
};


#endif //PORTAL_MAP_H
