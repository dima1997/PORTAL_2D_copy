//
// Created by franciscosicardi on 25/06/19.
//

#include "client_coord_action.h"

ClientCoordAction::ClientCoordAction(uint8_t playerId): ClientAction(playerId), xMap(), yMap() {}

Connector &ClientCoordAction::receiveFrom(Connector &out) {
    return out >> xMap >> yMap;
}

ClientCoordAction::~ClientCoordAction() = default;
