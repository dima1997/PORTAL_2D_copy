//
// Created by franciscosicardi on 02/06/19.
//

#include <yaml-cpp/node/node.h>
#include <configs_yaml/config_paths.h>
#include <yaml-cpp/yaml.h>
#include "map.h"

Map::Map(uint8_t map_id): file(YAML::LoadFile(CONFIG_PATHS.at(map_id))),
                          players_number(file["player_number"].as<int>()) {}

uint8_t Map::getPlayersNumber() {
    return players_number;
}

uint32_t Map::getPlayerId(uint8_t i) {
    return file["chells"]["id_coordinates"][i]["id"].as<uint32_t>();
}

Cake *Map::loadCake(b2World &world) {
    YAML::Node cakeIdCoords = file["cakes"]["id_coordinates"];
    auto id = cakeIdCoords[0]["id"].as<uint32_t>();
    auto x = cakeIdCoords[0]["xCoord"].as<float32>();
    auto y = cakeIdCoords[0]["yCoord"].as<float32>();
    return new Cake(world, x, y, id);
}

void Map::loadBlocks(b2World &world, std::list<Block *> &blocks_list) {
    YAML::Node metalBlocks = file["blocks_metal"]["id_coordinates"];
    for(auto &&block : metalBlocks) {
        blocks_list.push_back(loadBlock(block, world, METAL_BLOCK));
    }
    YAML::Node rockBlocks = file["blocks_rock"]["id_coordinates"];
    for(auto &&block : rockBlocks) {
        blocks_list.push_back(loadBlock(block, world, ROCK_BLOCK));
    }
    YAML::Node acidBlocks = file["blocks_acid"]["id_coordinates"];
    for(auto &&block : acidBlocks) {
        blocks_list.push_back(loadBlock(block, world, ACID_BLOCK));
    }
}

void Map::loadChells(b2World &world, std::list<Chell *> &chells) {
    YAML::Node chellsCoord = file["chells"]["id_coordinates"];
    const YAML::Node &bluePortalCoords = file["portals_blue"]["id_coordinates"];
    const YAML::Node &orangePortalCoords = file["portals_orange"]["id_coordinates"];
    for (int i = 0; i < (int)chellsCoord.size(); ++i) {
        Portal *bluePortal = loadPortal(bluePortalCoords[i], world);
        Portal *orangePortal = loadPortal(orangePortalCoords[i], world);
        chells.push_back(loadChell(chellsCoord[i], world, bluePortal, orangePortal));
    }
}

Portal *Map::loadPortal(const YAML::Node &portal, b2World &world) {
    auto id = portal["id"].as<uint32_t>();
    auto x = portal["xCoord"].as<float32>();
    auto y = portal["yCoord"].as<float32>();
    return new Portal(world, x, y, id);
}

Chell *Map::loadChell(const YAML::Node &chell, b2World &world, Portal *bluePortal, Portal *orangePortal) {
    auto id = chell["id"].as<uint32_t>();
    auto x = chell["xCoord"].as<float32>();
    auto y = chell["yCoord"].as<float32>();
    return new Chell(world, x, y, id, bluePortal, orangePortal);
}

Block *Map::loadBlock(const YAML::Node &block, b2World &world, body_type_t type) {
    auto id = block["id"].as<uint32_t>();
    auto x = block["xCoord"].as<float32>();
    auto y = block["yCoord"].as<float32>();
    return new Block(world, x, y, type, id);
}

void Map::loadDoors(b2World &world, std::list<Door *> &doors) {
    YAML::Node doorsInfo = file["doors_one"]["id_coordinates"];
    for (auto && doorInfo : doorsInfo) {
        std::unordered_map<uint32_t, bool> conditions;
        for (auto condition : doorInfo["conditions"]) {
            auto button_id = condition["button_id"].as<uint32_t>();
            auto cond = condition["condition"].as<bool>();
            conditions.insert(std::make_pair(button_id, cond));
        }
        auto id = doorInfo["id"].as<uint32_t>();
        auto x = doorInfo["xCoord"].as<float32>();
        auto y = doorInfo["yCoord"].as<float32>();
        doors.push_back(new Door(world, x, y, id, conditions));
    }
}

void Map::loadButtons(b2World &world, std::list<Button *> &buttons, std::list<Door *> &doors) {
    YAML::Node buttonsInfo = file["buttons"]["id_coordinates"];
    for (auto && buttonInfo : buttonsInfo) {
        std::list<Door *> buttonDoors;
        for (auto && doorIdNode : buttonInfo["door_ids"]) {
            auto doorId = doorIdNode.as<uint32_t>();
            for (auto door : doors) {
                if (door->getId() == doorId) {
                    buttonDoors.push_back(door);
                    break;
                }
            }
        }
        auto id = buttonInfo["id"].as<uint32_t>();
        auto x = buttonInfo["xCoord"].as<float32>();
        auto y = buttonInfo["yCoord"].as<float32>();
        buttons.push_back(new Button(world, x, y, id, buttonDoors));
    }

}
