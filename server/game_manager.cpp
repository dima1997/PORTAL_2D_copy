//
// Created by franciscosicardi on 09/05/19.
//

#include "game_manager.h"
#include "../common/protocol/protocol_code.h"
#include "../common/portal_exception.h"

GameManager::GameManager(): games(), mutex(), biggestKey(0) {}

void GameManager::addGame(Connector &connector, uint8_t map_id) {
    std::unique_lock<std::mutex> l(mutex);
    uint8_t game_id = this->getKey();
    Game game(game_id, map_id, connector);
    game.startIfReady();
    games.insert({game_id, std::move(game)});
    this->eraseFinished();
}

void GameManager::joinToGame(uint8_t gameId, Connector &connector) {
    std::unique_lock<std::mutex> l(mutex);
    try {
        Game &game = games.at(gameId);
        if (game.addPlayer(connector)) {
            game.startIfReady();
        } else {
            connector << game_is_full;
        }
    } catch (const std::out_of_range &e) {
        connector << non_existent_game;
    }
}

void GameManager::eraseFinished() {
    uint8_t biggest = 0;
    for (uint8_t i = 0; i <= biggestKey; i++) {
        if (games.count(i) > 0) {
            if (games.at(i).isFinished()) {
                games.at(i).join();
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

GameManager::~GameManager() {
    for (auto &it: games) {
        it.second.join();
    }
}
