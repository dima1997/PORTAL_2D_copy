//
// Created by franciscosicardi on 02/06/19.
//

#ifndef PORTAL_MAP_H
#define PORTAL_MAP_H


#include <cstdint>
#include <yaml-cpp/node/node.h>

class Map {
    YAML::Node file;
    uint8_t players_number;
public:
    explicit Map(uint8_t map_id);
    uint8_t getPlayersNumber();
    YAML::Node &getFile();
    uint32_t getPlayerId(uint8_t i);
};


#endif //PORTAL_MAP_H
