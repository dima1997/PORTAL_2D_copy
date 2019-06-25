//
// Created by franciscosicardi on 25/06/19.
//

#include "jump_action.h"

JumpAction::JumpAction(GameActionName gameActionName, uint8_t playerId) : ClientAction(gameActionName,
                                                                                               playerId) {}

void JumpAction::_execute(World &world) {
    world.getChell(playerId).updateState(JUMP);
}

JumpAction::~JumpAction() = default;
