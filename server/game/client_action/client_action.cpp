//
// Created by franciscosicardi on 25/06/19.
//

#include "client_action.h"

ClientAction::ClientAction(GameActionName gameActionName, uint8_t playerId): gameActionName(gameActionName), playerId(playerId) {}

ClientAction::ClientAction(const ClientAction &other): gameActionName(other.gameActionName), playerId(other.playerId) {}

Connector &ClientAction::receiveFrom(Connector &out) {
    uint8_t name;
    out >> name;
    gameActionName = (GameActionName) name;
    return out;
}

Connector &operator>>(Connector &out, ClientAction &action) {
    return action.receiveFrom(out);
}

void ClientAction::execute(World &world) {
    _execute(world);
}

ClientAction::~ClientAction() = default;
