//
// Created by franciscosicardi on 02/06/19.
//

#ifndef PORTAL_MAP_H
#define PORTAL_MAP_H


#include <cstdint>
#include <yaml-cpp/node/node.h>
#include "body/cake.h"
#include "body/chell.h"

class Map {
    YAML::Node file;
    uint8_t players_number;
public:
    explicit Map(uint8_t map_id);
    uint8_t getPlayersNumber();
    uint32_t getPlayerId(uint8_t i);
    Cake *loadCake(b2World &world);
    void loadBlocks(b2World &world, std::list<Body *> &blocks);
    void loadChells(b2World &world, std::list<Chell *> &chells);
};


#endif //PORTAL_MAP_H
