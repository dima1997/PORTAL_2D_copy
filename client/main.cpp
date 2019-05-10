//
// Created by franciscosicardi on 08/05/19.
//

#include <string>
#include "client.h"

int main(int argc, char **argv) {
    std::string host = "localhost";
    std::string port = "8082";
    std::string command = "new";
    if (argc == 4) {
        host = argv[1];
        port = argv[2];
        command = argv[3];
    }
    Client client(host, port, command);
    client();
    return 0;
}