//
// Created by franciscosicardi on 08/05/19.
//

#include <string>
#include "server/server.h"
#include "config/global_configuration.h"

int main(int argc, char **argv) {
    std::string port = CONFIG.defaultPort;
    if (argc == 2) {
        port = argv[1];
    } else if (argc > 2) {
        return 1;
    }
    Server server(port);
    server();
    return 0;
}