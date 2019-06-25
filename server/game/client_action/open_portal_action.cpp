//
// Created by franciscosicardi on 25/06/19.
//

#include "open_portal_action.h"

void OpenPortalAction::_execute(World &world) {
    world.getChell(playerId).shootPortal(xMap, yMap, color);
}

OpenPortalAction::OpenPortalAction(GameActionName gameActionName, uint8_t playerId, portal_color_t portalColor):
                                   ClientCoordAction(gameActionName, playerId), color(portalColor) {}

OpenPortalAction::~OpenPortalAction() = default;
