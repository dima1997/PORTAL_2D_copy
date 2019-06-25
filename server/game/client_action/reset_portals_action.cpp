//
// Created by franciscosicardi on 25/06/19.
//

#include "reset_portal_action.h"

ResetPortalAction::ResetPortalAction(uint8_t playerId) : ClientAction(playerId) {}

void ResetPortalAction::_execute(World &world) {
    world.getChell(playerId).resetPortals(); 
}

ResetPortalAction::~ResetPortalAction() = default;
