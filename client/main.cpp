#include "includes/game/client.h"
#include "includes/textures/common_texture/sdl_exception.h"
#include "includes/window/os_exception.h"
#include <portal_exception.h>

#include <exception> 
#include <iostream>
#include <string>

#define ERROR_ARGS 1
#define ERROR_SDL 2
#define ERROR_PORTAL 3
#define ERROR_OS 4
#define ERROR_UNEXPECTED 5

int main(int argc, char **argv) {
    try {
        bool wrongUse = false;
        if (argc == 5) {
            std::string host = argv[1];
            std::string port = argv[2];
            std::string command = argv[3];
            uint8_t id = (uint8_t)std::stoul(argv[4]);
            Client client;
            client(host, port, command, id);
        }  
        if (argc == 2){
            std::string mode = argv[1];
            if (mode == "line"){
                Client client;
                client.run_line();
            } else if (mode == "window"){
                Client client;
                client.run_qt(argc, argv);
            } else {
                wrongUse = true;
            }
        }
        if ((argc != 2 && argc != 5) || (wrongUse)) {
            std::cerr << "Usage:\n\t" << argv[0] << " host port command id" << std::endl;
            std::cerr << "or" << std::endl;
            std::cerr << "Usage:\n\t" << argv[0] << " line" << std::endl;
            std::cerr << "or" << std::endl;
            std::cerr << "Usage:\n\t" << argv[0] << " window" << std::endl;
            return ERROR_ARGS;
        }
    } catch (SdlException & error){
        std::cerr << error.what() << "\n";
        return ERROR_SDL;
    } catch (OSException & error){
        std::cerr << error.what() << "\n";
        return ERROR_OS;
    } catch (PortalException & error){
        std::cerr << error.what() << "\n";
        return ERROR_PORTAL;
    } catch (std::exception & error){
        std::cerr << error.what() << "\n";
        return ERROR_UNEXPECTED;
    }
    return 0;
}
