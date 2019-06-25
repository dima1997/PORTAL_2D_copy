//
// Created by franciscosicardi on 25/06/19.
//

#include "jump_action.h"

JumpAction::JumpAction(uint8_t playerId) : ClientAction(playerId) {}

void JumpAction::_execute(World &world) {
    world.getChell(playerId).updateState(JUMP);
}

JumpAction::~JumpAction() = default;
