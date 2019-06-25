//
// Created by franciscosicardi on 25/06/19.
//

#include "throw_left_action.h"

ThrowLeftAction::ThrowLeftAction(uint8_t playerId) : ClientAction(playerId) {}

void ThrowLeftAction::_execute(World &world) {
    world.getChell(playerId).throwRock(THROW_LEFT);
}

ThrowLeftAction::~ThrowLeftAction() = default;
