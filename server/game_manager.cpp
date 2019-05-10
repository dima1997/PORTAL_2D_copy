//
// Created by franciscosicardi on 09/05/19.
//

#include "game_manager.h"
#include "../common/protocol_code.h"

GameManager::GameManager(): games(), mutex() {}

void GameManager::addGame(Connector &connector, uint8_t mapId) {
    std::unique_lock<std::mutex> l(mutex);
    // TODO: capaz usar un GameFactory según em mapId
    Game game(games.size());
    game.addPlayer(connector);
    games.push_back(std::move(game));
}

void GameManager::joinToGame(uint8_t gameId, Connector &connector) {
    try {
        Game &game = games.at(gameId);
        if (!game.addPlayer(connector)) {
            connector << game_is_full;
        }
    } catch (const std::out_of_range &e) {
        connector << non_existent_game;
    }
}

GameManager::~GameManager() = default;
