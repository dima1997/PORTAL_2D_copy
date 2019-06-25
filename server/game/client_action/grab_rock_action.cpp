//
// Created by franciscosicardi on 25/06/19.
//

#include "grab_rock_action.h"

GrabRockAction::GrabRockAction(GameActionName gameActionName, uint8_t playerId) : ClientAction(gameActionName,
                                                                                               playerId) {}

void GrabRockAction::_execute(World &world) {
    world.getChell(playerId).grabRock();
}

GrabRockAction::~GrabRockAction() = default;
