//
// Created by franciscosicardi on 25/06/19.
//

#include "move_right_action.h"

MoveRightAction::MoveRightAction(uint8_t playerId) : ClientAction(playerId) {}

void MoveRightAction::_execute(World &world) {
    world.getChell(playerId).updateState(RIGHT);
}

MoveRightAction::~MoveRightAction() = default;
