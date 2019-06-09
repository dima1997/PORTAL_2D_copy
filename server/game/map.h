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

class Map {
    YAML::Node file;
    uint8_t players_number;
    Portal *loadPortal(const YAML::Node &portal, b2World &world);
    Chell *loadChell(const YAML::Node &chell, b2World &world, Portal *bluePortal, Portal *orangePortal);
    Block *loadBlock(const YAML::Node &block, b2World &world, body_type_t type);
public:
    explicit Map(uint8_t map_id);
    uint8_t getPlayersNumber();
    uint32_t getPlayerId(uint8_t i);
    Cake *loadCake(b2World &world);
    void loadBlocks(b2World &world, std::list<Block *> &blocks);
    void loadChells(b2World &world, std::list<Chell *> &chells);
    void loadDoors(b2World &world, std::list<Door *> &doors);
    void loadButtons(b2World &world, std::list<Button *> &buttons, std::list<Door *> &doors);
};


#endif //PORTAL_MAP_H
