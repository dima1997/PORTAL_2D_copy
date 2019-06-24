#include "../../includes/game/game_config.h"

#include "../../includes/game/game.h"

#include <connector/connector.h>
#include <cstdint>

GameConfig::GameConfig()
:   connector(),
    gameId(0),
    playerId(0),
    mapYaml(""),
    isWellConfig(false) {}

/*
Inicializa una configuracion de 
juego.
*/
GameConfig::GameConfig(
    Connector & connector,
    uint8_t gameId,
    uint32_t playerId,
    const std::string & mapYaml
)
:   connector(std::move(connector)),
    gameId(gameId),
    playerId(playerId),
    mapYaml(mapYaml),
    isWellConfig(true) {}

GameConfig::~GameConfig() = default;

GameConfig::GameConfig(GameConfig && other)
:   connector(std::move(other.connector)) {
    this->gameId = other.gameId;
    this->playerId = other.playerId;
    this->mapYaml = std::move(other.mapYaml);
    this->isWellConfig = other.isWellConfig;
    other.gameId = 0;
    other.playerId = 0;
    other.mapYaml = "";
    other.isWellConfig = false;
}

GameConfig & GameConfig::operator=(GameConfig && other){
    if (this == & other){
        return *this;
    }
    this->connector = std::move(other.connector);
    this->gameId = other.gameId;
    this->playerId = other.playerId;
    this->mapYaml = std::move(other.mapYaml);
    this->isWellConfig = other.isWellConfig;
    other.gameId = 0;
    other.playerId = 0;
    other.mapYaml = "";
    other.isWellConfig = false;
}


void GameConfig::set_connector(Connector & connector){
    this->connector = std::move(connector);
}

void GameConfig::set_game_id(uint8_t id){
    this->gameId = id;
}

void GameConfig::set_player_id(uint32_t id){
    this->playerId = id;
}

void GameConfig::set_map(const std::string & mapYaml){
    this->mapYaml = mapYaml;
}

void GameConfig::set_well_config(){
    this->isWellConfig = true;
}

bool GameConfig::is_well_config(){
    return this->isWellConfig;
} 

Game GameConfig::create_game(){
    return std::move(Game(
        this->connector, 
        this->gameId, 
        this->playerId, 
        this->mapYaml
    ));
}