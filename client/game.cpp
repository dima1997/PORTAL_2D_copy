//
// Created by franciscosicardi on 12/05/19.
//

#include "game.h"

Game::Game(Connector &connector, uint8_t game_id, uint8_t player_id):
            connector(std::move(connector)), gameId(game_id), playerId(player_id) {}

void Game::operator()() {
    uint8_t finished;
    connector >> finished;
}
