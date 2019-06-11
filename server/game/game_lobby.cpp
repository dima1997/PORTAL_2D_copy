//
// Created by franciscosicardi on 09/05/19.
//

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <protocol/protocol_code.h>
#include <protocol/event/object_moves_event.h>
#include <protocol/event/player_wins_event.h>
#include <portal_exception.h>
#include <chrono>
#include <protocol/event/player_dies_event.h>
#include "game_lobby.h"

#include <protocol/game_action/game_action.h>
#include <protocol/game_action/coords_action.h>
#include <protocol/event/object_switch_event.h>
#include <memory>

#include <iostream>

#include <configs_yaml/config_paths.h>
#include "yaml-cpp/yaml.h"

#define TIME_WAIT_MICRO_SECONDS 10000
#define ONE_SECOND_EQ_MICRO_SECONDS 100000 

GameLobby &GameLobby::operator=(GameLobby &&other) noexcept {
    this->id = other.id;
    this->ready = other.ready;
    this->players = std::move(other.players);
    this->playerIds = std::move(other.playerIds);
    this->game = std::move(other.game);
    return *this;
}

GameLobby::GameLobby(GameLobby &&other) noexcept: id(other.id), players(std::move(other.players)), mutex(), cv(),
                                   ready(other.ready), playerIds(std::move(other.playerIds)), map(std::move(other.map)),
                                   game(std::move(other.game)), gameName(std::move(other.gameName)) {}

GameLobby::GameLobby(uint8_t id, uint8_t map_id, Connector &connector, std::string &gameName):
                     id(id), players(), mutex(), cv(), ready(false),playerIds(), map(map_id),
                     game(), gameName(std::move(gameName)) {
    try {
        connector << (uint8_t) command_ok;
        connector << (uint8_t) id;
        std::unique_lock<std::mutex> l(mutex);
        uint32_t playerId = map.getPlayerId(0);
        connector << (uint32_t) playerId;
        players.push_back(std::move(connector));
    } catch(SocketException &se) {
        std::cerr << se.what();
    }

}

bool GameLobby::addPlayer(Connector &connector) {
    std::unique_lock<std::mutex> l(mutex);
    if (!ready) {
        try {
            connector << (uint8_t) command_ok;
            uint32_t playerId = map.getPlayerId(players.size());
            connector << playerId;
            players.push_back(std::move(connector));
            return true;
        } catch(SocketException &se) {
            std::cerr << se.what();
        }
    }
    return false;
}

GameLobby::~GameLobby() = default;

void GameLobby::startIfReady() {
    std::unique_lock<std::mutex> l(mutex);
    if (players.size() == map.getPlayersNumber() && !ready) {
        ready = true;
        game = std::unique_ptr<Game>(new Game(players, map));
        (*game)();
    }
}

bool GameLobby::isFinished() {
    if(game == nullptr) return false;
    return game->isFinished();
}

std::string &GameLobby::getName() {
    return gameName;
}

bool GameLobby::isReady() {
    return ready;
}

uint8_t GameLobby::getId() {
    return id;
}
