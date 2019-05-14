//
// Created by franciscosicardi on 08/05/19.
//

#include <string>
#include "server.h"

#define DEFAULT_PORT "8082"

int main(int argc, char **argv) {
    std::string port = DEFAULT_PORT;
    if (argc == 2) {
        port = argv[1];
    } else if (argc > 2) {
        return 1;
    }
    Server server(port);
    server();
    return 0;
}