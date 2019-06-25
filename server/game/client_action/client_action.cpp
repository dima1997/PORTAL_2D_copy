//
// Created by franciscosicardi on 25/06/19.
//

#include "client_action.h"

ClientAction::ClientAction(uint8_t playerId): playerId(playerId) {}

ClientAction::ClientAction(const ClientAction &other): playerId(other.playerId) {}

Connector &ClientAction::receiveFrom(Connector &out) {
    return out;
}

Connector &operator>>(Connector &out, ClientAction &action) {
    return action.receiveFrom(out);
}

void ClientAction::execute(World &world) {
    _execute(world);
}

ClientAction::~ClientAction() = default;
