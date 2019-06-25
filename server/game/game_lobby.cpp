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

#include "yaml-cpp/yaml.h"

GameLobby &GameLobby::operator=(GameLobby &&other) noexcept {
    this->id = other.id;
    this->game = std::move(other.game);
    return *this;
}

GameLobby::GameLobby(GameLobby &&other) noexcept: id(other.id), mutex(), cv(),
                     game(std::move(other.game)), gameName(std::move(other.gameName)) {}

GameLobby::GameLobby(uint8_t id, uint8_t map_id, Connector &connector, std::string &gameName):
                     id(id), mutex(), cv(), game(), gameName(std::move(gameName)) {
    try {
        std::unique_lock<std::mutex> l(mutex);
        connector << (uint8_t) command_ok;
        connector << (uint8_t) id;
        game = std::unique_ptr<Game>(new Game(connector, map_id));
        startIfReady();
    } catch(SocketException &se) {
        std::cerr << se.what() << std::endl;
    }

}

bool GameLobby::addPlayer(Connector &connector) {
    std::unique_lock<std::mutex> l(mutex);
    if (game->getState() == WAITING) {
        try {
            connector << (uint8_t) command_ok;
            game->addPlayer(connector);
            startIfReady();
            return true;
        } catch(SocketException &se) {
            std::cerr << se.what() << std::endl;
        }
    }
    return false;
}

GameLobby::~GameLobby() {
    if (game != nullptr) {
        game->join();
    }
}

void GameLobby::startIfReady() {
    if (game->getState() == READY) {
        (*game)();
    }
}

bool GameLobby::isFinished() {
    std::unique_lock<std::mutex> l(mutex);
    return game->getState() == FINISHED;
}

std::string &GameLobby::getName() {
    return gameName;
}

bool GameLobby::isReady() {
    std::unique_lock<std::mutex> l(mutex);
    return game->getState() == READY;
}

uint8_t GameLobby::getId() {
    return id;
}
