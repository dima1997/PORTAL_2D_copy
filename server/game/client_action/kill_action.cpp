//
// Created by franciscosicardi on 25/06/19.
//

#include "kill_action.h"

KillAction::KillAction(GameActionName gameActionName, uint8_t playerId) : ClientAction(gameActionName,
                                                                                               playerId) {}

void KillAction::_execute(World &world) {
    world.getChell(playerId).die();
}

KillAction::~KillAction() = default;
