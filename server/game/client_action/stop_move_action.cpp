//
// Created by franciscosicardi on 25/06/19.
//

#include "stop_move_action.h"

StopMoveAction::StopMoveAction(GameActionName gameActionName, uint8_t playerId) : ClientAction(gameActionName,
                                                                                               playerId) {}

void StopMoveAction::_execute(World &world) {
    world.getChell(playerId).updateState(STOP);
}

StopMoveAction::~StopMoveAction() = default;
