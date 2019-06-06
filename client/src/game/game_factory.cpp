#include "../../includes/game/game_factory.h"

#include <iostream>
#include <sstream>
#include <connector/connector.h>
#include <protocol/protocol_code.h>
#include <portal_exception.h>

#include <iostream>
#include <sstream>

GameFactory::GameFactory() = default;
GameFactory::~GameFactory() = default;

Game GameFactory::createGame(std::string &host, std::string &port, std::string &command, uint8_t id) {
    Connector connector(host, port);
    if (command == "new") {
        /*
        connector << (uint8_t) new_game;
        connector << (uint8_t) id;
        uint8_t status;
        connector >> status;
        std::cout << (unsigned) status << std::endl;
        uint8_t game_id;
        connector >> game_id;
        std::cout << (unsigned) game_id << std::endl;
        uint32_t player_id;
        connector >> player_id;
        return std::move(Game(connector, game_id, player_id));
        */
        return this->start_new_game(connector, id);
    }
    if (command == "join") {
        /*
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
        */
        return this->start_join_game(connector, id);
    }
}

Game GameFactory::start_new_game(Connector & connector, uint8_t mapId){
    connector << (uint8_t) new_game;
    connector << (uint8_t) mapId;
    uint8_t status;
    connector >> status;
    std::cout << (unsigned) status << std::endl;
    uint8_t game_id;
    connector >> game_id;
    std::cout << (unsigned) game_id << std::endl;
    uint32_t player_id;
    connector >> player_id;
    return std::move(Game(connector, game_id, player_id));
}

Game GameFactory::start_join_game(Connector & connector, uint8_t gameId){
    connector << (uint8_t) join_game;
    connector << (uint8_t) gameId;
    uint8_t status;
    connector >> status;
    std::cout << (unsigned) status << std::endl;
    if (status == command_ok) {
        uint8_t player_id;
        connector >> player_id;
        std::cout << (unsigned) player_id << std::endl;
        return std::move(Game(connector, gameId, player_id));
    } else if (status == game_is_full) {
        std::stringstream msg;
        msg << "Game " << (unsigned) gameId << " is full." << std::endl;
        throw PortalException(msg.str());
    } else if (status == non_existent_game) {
        std::stringstream msg;
        msg << "Game " << (unsigned) gameId << " does not exist." << std::endl;
        throw PortalException(msg.str());
    } else {
        throw PortalException("Unexpected error...\n");
    }
}