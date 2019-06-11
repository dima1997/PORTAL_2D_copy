#include "../../includes/game/game_config.h"

#include "../../includes/game/game.h"

#include <connector/connector.h>
#include <cstdint>

GameConfig::GameConfig() {}

GameConfig::~GameConfig() = default;

void GameConfig::set_connector(Connector & connector){
    this->connector = std::move(connector);
}

void GameConfig::set_game_id(uint8_t id){
    this->gameId = id;
}

void GameConfig::set_player_id(uint32_t id){
    this->playerId = id;
}

void GameConfig::set_map_id(uint8_t id){
    this->mapId = id;
}

Game GameConfig::create_game(){
    return std::move(Game(
        this->connector, 
        this->gameId, 
        this->playerId, 
        this->mapId
    ));
}