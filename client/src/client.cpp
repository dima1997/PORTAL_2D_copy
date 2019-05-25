//
// Created by franciscosicardi on 10/05/19.
//

#include <iostream>
#include "client.h"
#include "../../common/protocol_code.h"
#include "game_factory.h"

Client::Client() = default;

void Client::operator()(std::string &host, std::string &port, std::string &command, uint8_t id) {
    Game game = GameFactory::createGame(host, port, command, id);
}
