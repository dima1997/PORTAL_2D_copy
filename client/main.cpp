#include "includes/textures/common_texture/sdl_exception.h"
#include "includes/window/os_exception.h"
#include "includes/game/client.h"

#include <iostream>
#include <exception> 
#include <string>
#include <iostream>

#include <QApplication>
#include <QLabel>

int main(int argc, char **argv) {
    /*
    {
        QApplication app(argc, argv);
        QLabel label("Por favor, funciona.");
        label.show();
        app.exec();
    }

    std::setlocale(LC_NUMERIC,"C");
    */
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
            return 1;
        }
    } catch (SdlException &error){
        std::cout << error.what() << "\n";
        return 2;
    } catch (OSException &error){
        std::cout << error.what() << "\n";
        return 3;
    } catch (std::exception &error){
        std::cout << error.what() << "\n";
        return 4;
    }
    return 0;
}
