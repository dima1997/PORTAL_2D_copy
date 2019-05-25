#include "includes/tests/animation_tests_2.h"
#include "includes/textures/common_texture/sdl_exception.h"
#include "includes/window/os_exception.h"

#include <iostream>
#include <exception> 

#include <string>
#include "src/client.h"
#include "src/game_factory.h"

int main(int argc, char **argv) {
    try {
        if (argc != 5) {
            exit(1);
        }
        std::string host = argv[1];
        std::string port = argv[2];
        std::string command = argv[3];
        uint8_t id = (uint8_t)std::stoul(argv[4]);
        Client client;
        client(host, port, command, id);
        testUserGameAnimationProxy();
    } catch (SdlException &error){
        std::cout << error.what() << "\n";
        return 1;
    } catch (OSException &error){
        std::cout << error.what() << "\n";
        return 2;
    } catch (std::exception &error){
        std::cout << error.what() << "\n";
        return 3;
    }
    return 0;
}
