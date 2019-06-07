#include "../../includes/game/client.h"

#include "../../includes/game/game_factory.h"
#include "../../includes/user_interface/login.h"

#include <protocol/protocol_code.h>
#include <iostream>

#include <QApplication>

Client::Client() = default;

/*Ejecuta el juego sin ventanas qt*/
void Client::operator()(std::string &host, std::string &port, std::string &command, uint8_t id) {
    GameFactory gameFactory;
    Game game = gameFactory.createGame(host, port, command, id);
    game();
}

/*Ejecuta el juego con ventanas qt*/
void Client::run(std::string &host, std::string &port, int argc, char **argv){
    bool newed = false;
    uint8_t mapId;
    bool joined = false;
    uint8_t gameId;
    LoginEvent loginEvent = NO_LOGIN;
    {
        QApplication app(argc, argv);
        LoginNew loginNew(newed, mapId);
        
        LoginJoin loginJoin(joined, gameId);

        Login login(loginEvent, loginNew, loginJoin);
        
        login.show();

        app.exec();
    }
    
    Connector connector(host, port);
    GameFactory gameFactory;

    if (loginEvent == NEW_LOGIN){
        std::cout << "New game option selected : ";
        if (newed){
            std::cout << "Map id selected : " << (unsigned) mapId << "\n";
            Game game = gameFactory.start_new_game(connector, mapId);
            game();
        } else {
            std::cout << "Not game newed\n";
        }
    } else if (loginEvent == JOIN_LOGIN){
        std::cout << "Join game option selected : ";
        if (joined){
            std::cout << "Game id selected : " << (unsigned) gameId << "\n";
            Game game = gameFactory.start_join_game(connector, gameId);
            game();
        } else {
            std::cout << "Not game joined\n";
        }
    } else {
        std::cout << "Not new/join option selected\n";
    }
    
}

