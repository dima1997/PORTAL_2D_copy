//
// Created by franciscosicardi on 25/06/19.
//

#include "quit_game_action.h"

QuitGameAction::QuitGameAction(uint8_t playerId) : ClientAction(playerId) {}

void QuitGameAction::_execute(World &world) {
    world.getChell(playerId).die();
}

QuitGameAction::~QuitGameAction() = default;
