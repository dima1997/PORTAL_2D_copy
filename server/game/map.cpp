//
// Created by franciscosicardi on 02/06/19.
//

#include <yaml-cpp/node/node.h>
#include <configs_yaml/config_paths.h>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include "map.h"

Map::Map(uint8_t map_id): id(map_id), file(YAML::LoadFile(CONFIG_PATHS.at(map_id))),
                          players_number(file["player_number"].as<int>()) {}

uint8_t Map::getPlayersNumber() {
    return players_number;
}

uint32_t Map::getPlayerId(uint8_t i) {
    return file["chells"]["id_coordinates"][i]["id"].as<uint32_t>();
}

Cake Map::loadCake(b2World &world) {
    YAML::Node cakeIdCoords = file["cakes"]["id_coordinates"];
    auto id = cakeIdCoords[0]["id"].as<uint32_t>();
    auto x = cakeIdCoords[0]["xCoord"].as<float32>();
    auto y = cakeIdCoords[0]["yCoord"].as<float32>();
    return Cake(world, x, y, id);
}

std::list<Block> Map::loadBlocks(b2World &world) {
    YAML::Node metalBlocks = file["blocks_metal"]["id_coordinates"];
    std::list<Block> blocks_list;
    for(auto &&block : metalBlocks) {
        blocks_list.push_back(std::move(loadBlock(block, world, METAL_BLOCK, SQUARE)));
    }
    YAML::Node rockBlocks = file["blocks_rock"]["id_coordinates"];
    for(auto &&block : rockBlocks) {
        blocks_list.push_back(std::move(loadBlock(block, world, ROCK_BLOCK, SQUARE)));
    }
    YAML::Node acidBlocks = file["blocks_acid"]["id_coordinates"];
    for(auto &&block : acidBlocks) {
        blocks_list.push_back(std::move(loadBlock(block, world, ACID_BLOCK, SQUARE)));
    }

    YAML::Node bottom_left = file["triangles_botom_left"]["id_coordinates"];
    for(auto &&block : bottom_left) {
        blocks_list.push_back(std::move(loadBlock(block, world, METAL_BLOCK, BOTTOM_LEFT)));
    }
    YAML::Node bottom_right = file["triangles_botom_right"]["id_coordinates"];
    for(auto &&block : bottom_right) {
        blocks_list.push_back(std::move(loadBlock(block, world, METAL_BLOCK, BOTTOM_RIGHT)));
    }
    YAML::Node top_left = file["triangles_top_left"]["id_coordinates"];
    for(auto &&block : top_left) {
        blocks_list.push_back(std::move(loadBlock(block, world, METAL_BLOCK, TOP_LEFT)));
    }
    YAML::Node top_right = file["triangles_top_right"]["id_coordinates"];
    for(auto &&block : top_right) {
        blocks_list.push_back(std::move(loadBlock(block, world, METAL_BLOCK, TOP_RIGHT)));
    }
    return blocks_list;
}

std::list<Chell> Map::loadChells(b2World &world) {
    YAML::Node chellsCoord = file["chells"]["id_coordinates"];
    const YAML::Node &bluePortalCoords = file["portals_blue"]["id_coordinates"];
    const YAML::Node &orangePortalCoords = file["portals_orange"]["id_coordinates"];
    std::list<Chell> chells;
    for (int i = 0; i < (int)chellsCoord.size(); ++i) {
        Portal *bluePortal = loadPortal(bluePortalCoords[i], world);
        Portal *orangePortal = loadPortal(orangePortalCoords[i], world);
        chells.push_back(std::move(loadChell(chellsCoord[i], world, bluePortal, orangePortal)));
    }
    return chells;
}

Portal *Map::loadPortal(const YAML::Node &portal, b2World &world) {
    auto id = portal["id"].as<uint32_t>();
    auto x = portal["xCoord"].as<float32>();
    auto y = portal["yCoord"].as<float32>();
    return new Portal(world, x, y, id);
}

Chell Map::loadChell(const YAML::Node &chell, b2World &world, Portal *bluePortal, Portal *orangePortal) {
    auto maxHeight = file["background"]["height"].as<float32>();
    auto maxWidth = file["background"]["width"].as<float32 >();
    auto id = chell["id"].as<uint32_t>();
    auto x = chell["xCoord"].as<float32>();
    auto y = chell["yCoord"].as<float32>();
    return Chell(world, x, y, id, bluePortal, orangePortal, fmax(maxHeight, maxWidth));
}

Block Map::loadBlock(const YAML::Node &block, b2World &world, body_type_t type, orientation_t orientation) {
    auto id = block["id"].as<uint32_t>();
    auto x = block["xCoord"].as<float32>();
    auto y = block["yCoord"].as<float32>();
    return Block(world, x, y, type, id, orientation);
}

std::list<Door> Map::loadDoors(b2World &world) {
    YAML::Node doorsInfo = file["doors_one"]["id_coordinates"];
    std::list<Door> doors;
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
//        doors.push_back(std::move(Door(world, x, y, id, conditions)));
        doors.emplace_back(world, x, y, id, conditions);
    }
    return doors;
}

std::list<Button> Map::loadButtons(b2World &world, std::list<Door> &doors) {
    YAML::Node buttonsInfo = file["buttons"]["id_coordinates"];
    std::list<Button> buttons;
    for (auto && buttonInfo : buttonsInfo) {
        std::list<std::reference_wrapper<Door>> buttonDoors;
        for (auto && doorIdNode : buttonInfo["door_ids"]) {
            auto doorId = doorIdNode.as<uint32_t>();
            for (auto &door : doors) {
                if (door.getId() == doorId) {
                    buttonDoors.emplace_back(door);
                    break;
                }
            }
        }
        auto id = buttonInfo["id"].as<uint32_t>();
        auto x = buttonInfo["xCoord"].as<float32>();
        auto y = buttonInfo["yCoord"].as<float32>();
        buttons.emplace_back(world, x, y, id, buttonDoors);
    }
    return buttons;

}

void Map::loadRocks(b2World &world, std::list<Rock *> &rocks) {
    std::vector<std::string> rocksSections;
    rocksSections.emplace_back("rocks_one");
    rocksSections.emplace_back("rocks_two");
    rocksSections.emplace_back("rocks_three");
    rocksSections.emplace_back("rocks_four");
    rocksSections.emplace_back("rocks_five");
    rocksSections.emplace_back("rocks_six");
    rocksSections.emplace_back("rocks_seven");
    rocksSections.emplace_back("rocks_eight");
    // Esto puede romper si las secciones no existen
    for (int i = 0; i < (int)rocksSections.size(); ++i){
        std::string section = rocksSections[i];
        YAML::Node rocksInfo = file[section.c_str()]["id_coordinates"];
        for (auto && rockInfo : rocksInfo) {
            auto id = rockInfo["id"].as<uint32_t>();
            auto x = rockInfo["xCoord"].as<float32>();
            auto y = rockInfo["yCoord"].as<float32>();
            rocks.push_back(new Rock(world, x, y, id, 0.4f, 0.4f));
        }
    }
}

std::string Map::toString() {
    std::ifstream t(CONFIG_PATHS.at(id));
    return std::string((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
}

void Map::loadBarriers(b2World &world, std::list<Barrier *> &barriers) {
    YAML::Node barriersInfo = file["barriers"];
    for (auto && barrierInfo : barriersInfo) {
        auto id = barrierInfo["id"].as<uint32_t>();
        auto x = barrierInfo["xCoord"].as<float32>();
        auto y = barrierInfo["yCoord"].as<float32>();
        auto height = barrierInfo["height"].as<float32>();
        auto width = barrierInfo["width"].as<float32>();
        barriers.push_back(new Barrier(world, x, y, id, height/2, width/2));
    }
}

void Map::loadEmitters(b2World &world, std::list<EnergyEmitter *> &emmiters) {
    YAML::Node emittersInfo = file["emitters_right"]["id_coordinates"];
    for (auto && emitterInfo : emittersInfo) {
        emmiters.push_back(loadEmitter(emitterInfo, world, RIGHT_D));
    }
}

EnergyEmitter *Map::loadEmitter(const YAML::Node &emitterInfo, b2World &world, direction_t direction) {
    auto id = emitterInfo["id"].as<uint32_t>();
    auto x = emitterInfo["xCoord"].as<float32>();
    auto y = emitterInfo["yCoord"].as<float32>();
    return new EnergyEmitter(world, x, y, id, direction);
}

void Map::loadBalls(b2World &world, std::list<EnergyBall *> &balls, std::list<EnergyEmitter *> &emmiters) {
    YAML::Node ballsInfo = file["energy_balls_green"]["id_coordinates"];
    for (auto && ballInfo : ballsInfo) {
        auto id = ballInfo["id"].as<uint32_t>();
        auto x = ballInfo["xCoord"].as<float32>();
        auto y = ballInfo["yCoord"].as<float32>();
        auto emitterId = ballInfo["emitter"].as<uint32_t >();
        for (auto emitter : emmiters) {
            if (emitter->getId() == emitterId) {
                balls.push_back(new EnergyBall(world, x, y, id, *emitter));
                break;
            }
        }
    }
}
