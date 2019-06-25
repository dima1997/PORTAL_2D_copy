//
// Created by franciscosicardi on 25/06/19.
//

#include "kill_action.h"

KillAction::KillAction(uint8_t playerId) : ClientAction(playerId) {}

void KillAction::_execute(World &world) {
    world.getChell(playerId).die();
}

KillAction::~KillAction() = default;
