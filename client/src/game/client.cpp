#include "../../includes/game/client.h"

#include "../../includes/game/game_factory.h"
#include "../../includes/user_interface/line_interface.h"
#include "../../includes/user_interface/message_exception.h"

#include <connector/socket_exception.h>
#include <iostream>

Client::Client() = default;

void Client::operator()(std::string &host, std::string &port, std::string &command, uint8_t id) {
    Game game = GameFactory::createGame(host, port, command, id);
    game();
}

void Client::run(){
    bool keepInput = true;
    LineInterface lineaInterface(keepInput);
    while (keepInput){
        try {
            Game game = std::move(lineaInterface.create_game());
            game();
        } catch (MessageException &except) {
            std::cout << except.what() << "\n";
        } catch (SocketException &except) {
            std::cout << "Connection Lost at C.\n";
        }
    }
}