//
// Created by franciscosicardi on 25/06/19.
//

#include "pin_tool_action.h"

void PinToolAction::_execute(World &world) {
    world.getChell(playerId).showPinTool(xMap, yMap);
}

PinToolAction::PinToolAction(uint8_t playerId): ClientCoordAction(playerId) {}

PinToolAction::~PinToolAction() = default;
