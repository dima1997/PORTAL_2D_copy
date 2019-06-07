#include "includes/textures/common_texture/sdl_exception.h"
#include "includes/window/os_exception.h"
#include "includes/game/client.h"

#include <iostream>
#include <exception> 
#include <string>

#include <QApplication>
#include <QLabel>

void prueba_qt_ventanta(int argc, char** argv){
    QApplication app(argc, argv);

    QLabel label("Pleasssssssse work");
    label.show();

    app.exec();
}

int main(int argc, char **argv) {
    //prueba_qt_ventanta(argc, argv);
    try {
        Client client;
        if (argc == 5) {
            std::string host = argv[1];
            std::string port = argv[2];
            std::string command = argv[3];
            uint8_t id = (uint8_t)std::stoul(argv[4]);
            client(host, port, command, id);
        } else if (argc == 1) {
            std::string host = "localhost";
            std::string port = "8082";
            client.run(host, port, argc, argv);
        } else {
            std::cerr << "Usage:\n\t" << argv[0] << std::endl;
            std::cerr << "Usage:\n\t" << argv[0] << " host port command id" << std::endl;
            exit(1);    
        }
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
