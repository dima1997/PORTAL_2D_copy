//
// Created by franciscosicardi on 25/06/19.
//

#include "move_left_action.h"

MoveLeftAction::MoveLeftAction(GameActionName gameActionName, uint8_t playerId) : ClientAction(gameActionName,
                                                                                               playerId) {}

void MoveLeftAction::_execute(World &world) {
    world.getChell(playerId).updateState(LEFT);
}

MoveLeftAction::~MoveLeftAction() = default;
