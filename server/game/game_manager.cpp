//
// Created by franciscosicardi on 09/05/19.
//

#include "game_manager.h"
#include <protocol/protocol_code.h>
#include <portal_exception.h>
#include <iostream>
#include "../config/maps_configuration.h"

GameManager::GameManager(): games(), mutex(), biggestKey(0) {}

void GameManager::addGame(Connector &connector) {
    std::unique_lock<std::mutex> l(mutex);
    try {
        connector << (uint8_t) CONFIG_PATHS.size();
        for (const auto &map : CONFIG_PATHS) {
            connector << (uint8_t) map.first;
        }
        uint8_t mapId;
        std::string gameName;
        connector >> mapId;
        connector >> gameName;
        uint8_t game_id = this->getKey();
        games.insert(std::make_pair(game_id, GameLobby(game_id, mapId, connector, gameName)));
        this->eraseFinished();
    } catch(SocketException &se) {
        std::cerr << se.what() << std::endl;
    }
}

void GameManager::joinToGame(Connector &connector) {
    std::unique_lock<std::mutex> l(mutex);
    try {
        sendAvailableGames(connector);
        uint8_t gameId;
        connector >> gameId;
        try {
            GameLobby &game = games.at(gameId);
            if (!game.addPlayer(connector)) {
                connector << (uint8_t) game_is_full;
            }
        } catch (const std::out_of_range &e) {
            connector << (uint8_t) non_existent_game;
        }
    } catch(SocketException &se) {
        std::cerr << se.what() << std::endl;
    }
}

void GameManager::eraseFinished() {
    uint8_t biggest = 0;
    for (uint8_t i = 0; i <= biggestKey; i++) {
        if (games.count(i) > 0) {
            if (games.at(i).isFinished()) {
                games.erase(i);
            } else {
                if (i > biggest) biggest = i;
            }
        }
    }
    biggestKey = biggest;
}

uint8_t GameManager::getKey() {
    if (biggestKey < std::numeric_limits<uint8_t>::max()) {
        return ++biggestKey;
    }
    for (uint8_t i = 0; i < biggestKey; i++) {
        if (games.count(i) == 0) {
            return i;
        }
    }
    throw PortalException("A new game can't be added in this moment.");
}

GameManager::~GameManager() = default;

void GameManager::sendAvailableGames(Connector &connector) {
    auto availableGames = std::list<GameLobby *>();
    uint8_t availableGamesCount = 0;
    for (auto &game : games) {
        if (!game.second.isFinished() && !game.second.isReady()) {
            availableGames.push_back(&game.second);
            ++ availableGamesCount;
        }
    }
    connector << availableGamesCount;
    for (auto &game : availableGames) {
        connector << game->getId() << game->getName();
    }
}
