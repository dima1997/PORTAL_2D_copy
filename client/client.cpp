//
// Created by franciscosicardi on 10/05/19.
//

#include <iostream>
#include "client.h"
#include "../common/protocol_code.h"

Client::Client(std::string &host, std::string &port, std::string &command):
                connector(host, port), command(command) {}

void Client::operator()() {
    if (command == "new") {
        connector << new_game;
        connector << 1; // mapId harcodeado
        uint8_t status;
        connector >> status;
        std::cout << (unsigned) status << std::endl;
    }
    if (command == "join") {
        connector << join_game;
        connector << 1; // gameId harcodeado
        uint8_t status;
        connector >> status;
        std::cout << (unsigned) status << std::endl;
        if (status == command_ok) {
            uint8_t player_id;
            connector >> player_id;
            std::cout << (unsigned) player_id << std::endl;
        }
    }
}
