//
// Created by franciscosicardi on 12/05/19.
//

#include <iostream>
#include <sstream>
#include <protocol/protocol_code.h>
#include <portal_exception.h>
#include "game_factory.h"

GameFactory::GameFactory() = default;

Game GameFactory::createGame(std::string &host, std::string &port, std::string &command, uint8_t id) {
    Connector connector(host, port);
    if (command == "new") {
        connector << (uint8_t) new_game;
        connector << (uint8_t) id;
        uint8_t status;
        connector >> status;
        std::cout << (unsigned) status << std::endl;
        uint8_t game_id;
        connector >> game_id;
        std::cout << (unsigned) game_id << std::endl;
        return std::move(Game(connector, game_id, 0));
    }
    if (command == "join") {
        connector << (uint8_t) join_game;
        connector << (uint8_t) id;
        uint8_t status;
        connector >> status;
        std::cout << (unsigned) status << std::endl;
        if (status == command_ok) {
            uint8_t player_id;
            connector >> player_id;
            std::cout << (unsigned) player_id << std::endl;
            return std::move(Game(connector, id, player_id));
        } else if (status == game_is_full) {
            std::stringstream msg;
            msg << "Game " << (unsigned) id << " is full." << std::endl;
            throw PortalException(msg.str());
        } else if (status == non_existent_game) {
            std::stringstream msg;
            msg << "Game " << (unsigned) id << " does not exist." << std::endl;
            throw PortalException(msg.str());
        } else {
            throw PortalException("Unexpected error...\n");
        }
    }
}
