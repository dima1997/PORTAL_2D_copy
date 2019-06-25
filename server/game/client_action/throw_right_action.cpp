//
// Created by franciscosicardi on 25/06/19.
//

#include "throw_right_action.h"

ThrowRightAction::ThrowRightAction(uint8_t playerId) : ClientAction(playerId) {}

void ThrowRightAction::_execute(World &world) {
    world.getChell(playerId).throwRock(THROW_RIGHT);
}

ThrowRightAction::~ThrowRightAction() = default;
