//
// Created by franciscosicardi on 08/05/19.
//

#include <string>
#include <iostream>
#include "server/server.h"
#include "config/global_configuration.h"

int main(int argc, char **argv) {
    try {
        std::string port = CONFIG.defaultPort;
        if (argc == 2) {
            port = argv[1];
        } else if (argc > 2) {
            return 1;
        }
        Server server(port);
        server();
        return 0;    
    } catch (const std::exception &s) {
        std::cerr << s.what() << std::endl;
        return 1;
    } 
    
}