//
// Created by franciscosicardi on 08/05/19.
//

#include <string>
#include "client.h"
#include "game_factory.h"

int main(int argc, char **argv) {
    if (argc != 5) {
        exit(1);
    }
    std::string host = argv[1];
    std::string port = argv[2];
    std::string command = argv[3];
    uint8_t id = (uint8_t)std::stoul(argv[4]);
    Client client;
    client(host, port, command, id);
    return 0;
}