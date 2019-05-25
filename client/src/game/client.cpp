#include "../../includes/game/client.h"

#include "../../../common/protocol_code.h"
#include "../../includes/game/game_factory.h"

#include <iostream>

Client::Client() = default;

void Client::operator()(std::string &host, std::string &port, std::string &command, uint8_t id) {
    Game game = GameFactory::createGame(host, port, command, id);
}
