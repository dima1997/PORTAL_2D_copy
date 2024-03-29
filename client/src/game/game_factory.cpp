#include "../../includes/game/game_factory.h"

#include <iostream>
#include <sstream>
#include <connector/connector.h>
#include <protocol/protocol_code.h>
#include <portal_exception.h>

#include <iostream>
#include <sstream>

Game GameFactory::createGame(std::string &host, std::string &port, std::string &command, uint8_t id) {
    Connector connector(host, port);
    if (command == "new") {
        connector << (uint8_t) new_game;
        uint8_t mapsNumber;
        connector >> mapsNumber;
        for (uint8_t i = 0; i < mapsNumber; ++i) {
            uint8_t mapId;
            connector >> mapId;
        }
        connector << (uint8_t) id;
        connector << "Hard-coded game name";
        uint8_t status;
        connector >> status;
        std::cout << (unsigned) status << std::endl;
        uint8_t game_id;
        connector >> game_id;
        std::cout << (unsigned) game_id << std::endl;
        uint32_t player_id;
        connector >> player_id;
        std::string mapYaml;
        connector >> mapYaml;
        return std::move(Game(connector, game_id, player_id, mapYaml));
    }
    if (command == "join") {
        connector << (uint8_t) join_game;
        uint8_t gameCount;
        connector >> gameCount;
        for (uint8_t i = 0; i < gameCount; ++i) {
            uint8_t gameId;
            connector >> gameId;
            std::string gameName;
            connector >> gameName;
        }
        connector << (uint8_t) id;
        uint8_t status;
        connector >> status;
        std::cout << (unsigned) status << std::endl;
        if (status == command_ok) {
            uint32_t player_id;
            connector >> player_id;
            std::cout << (unsigned) player_id << std::endl;
            std::string mapYaml;
            connector >> mapYaml;
            return std::move(Game(connector, id, player_id, mapYaml));
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
    throw PortalException("Invalid command.\n");
}