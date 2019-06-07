//
// Created by franciscosicardi on 02/06/19.
//

#include <yaml-cpp/node/node.h>
#include <configs_yaml/config_paths.h>
#include <yaml-cpp/yaml.h>
#include "map.h"
#include "body/block.h"

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

void Map::loadBlocks(b2World &world, std::list<Body *> &blocks_list) {
    YAML::Node blocks = file["blocks"];
//    float widthBlock = blocks["width"].as<float>(); // TODO : Actualizar codigo para utilizar estos tamanios del YAML
//    float heightBlock = blocks["height"].as<float>(); //  Puedes usar float32 si gustas
    YAML::Node blocksIdCoords = blocks["id_material_coordinates"];
    for(auto && blocksIdCoord : blocksIdCoords) {
        auto id = blocksIdCoord["id"].as<uint32_t>();
        auto material = blocksIdCoord["material"].as<std::string>();
        auto x = blocksIdCoord["xCoord"].as<float32>();
        auto y = blocksIdCoord["yCoord"].as<float32>();
        if (material == "rock") {
            blocks_list.push_back(new Block(world, x, y, ROCK_BLOCK, id));
        } else if (material == "metal") {
            blocks_list.push_back(new Block(world, x, y, METAL_BLOCK, id));
        } else if (material == "acid") {
            blocks_list.push_back(new Block(world, x, y, ACID_BLOCK, id));
        }
    }
}

void Map::loadChells(b2World &world, std::list<Chell *> &chells) {
    YAML::Node chellsYaml = file["chells"];
//    float widthChell = chellsYaml["width"].as<float>();
//    float heightChell = chellsYaml["height"].as<float>();
    YAML::Node chellsIdCoords = chellsYaml["id_coordinates"];
    for (auto && chellsIdCoord : chellsIdCoords){
        auto id = chellsIdCoord["id"].as<uint32_t>();
        auto x = chellsIdCoord["xCoord"].as<float32>();
        auto y = chellsIdCoord["yCoord"].as<float32>();
        chells.push_back(new Chell(world, x, y, id));
    }
    YAML::Node portalsYaml = file["portals"];
//    float portalWidth = portalsYaml["width"].as<float>();
//    float portalHeight = portalsYaml["height"].as<float>();
    YAML::Node portalsIdColorCoords = portalsYaml["id_color_coordinates"];
    std::vector<Portal *> portals;
    for (auto && portalsIdColorCoord : portalsIdColorCoords){
        auto id = portalsIdColorCoord["id"].as<uint32_t>();
        auto color = portalsIdColorCoord["color"].as<std::string>();
        auto x = portalsIdColorCoord["xCoord"].as<float32>();
        auto y = portalsIdColorCoord["yCoord"].as<float32>();
        portals.push_back(new Portal(world, x, y, id));
        // Aqui se agregan los portales
    }
    int i = 0;
    for(auto chell : chells) {
        chell->setPortal(portals[i++], BLUE);
        chell->setPortal(portals[i++], ORANGE);
        connect(portals[i - 1], portals[i - 2]);
    }
}
