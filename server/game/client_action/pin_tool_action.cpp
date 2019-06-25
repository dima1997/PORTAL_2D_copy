//
// Created by franciscosicardi on 25/06/19.
//

#include "pin_tool_action.h"

void PinToolAction::_execute(World &world) {
    world.getChell(playerId).showPinTool(xMap, yMap);
}

PinToolAction::PinToolAction(GameActionName gameActionName, uint8_t playerId):
                             ClientCoordAction(gameActionName, playerId) {}

PinToolAction::~PinToolAction() = default;
