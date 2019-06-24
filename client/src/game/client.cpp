#include "../../includes/game/client.h"

#include "../../includes/game/game_factory.h"
#include "../../includes/game/game_config.h"
#include "../../includes/user_interface/line_interface.h"
#include "../../includes/user_interface/message_exception.h"
#include "../../includes/user_interface/login.h"
#include "../../includes/user_interface/game_over.h"
#include "../../includes/threads/play_result.h"

#include <connector/socket_exception.h>
#include <iostream>

#include <QApplication>

Client::Client() = default;

void Client::operator()(std::string &host, std::string &port, std::string &command, uint8_t id) {
    Game game = GameFactory::createGame(host, port, command, id);
    game();
}

void Client::run_line(){
    bool keepInput = true;
    LineInterface lineaInterface(keepInput);
    while (keepInput){
        try {
            GameConfig gameConfig = std::move(lineaInterface.create_game());
            if (! gameConfig.is_well_config()){
                continue;
            }
            Game game = std::move(gameConfig.create_game());
            PlayResult playResult = game();
            playResult.print();
        } catch (MessageException &except) {
            std::cout << except.what() << "\n";
        } catch (SocketException &except) {
            std::cout << "Connection Lost at C.\n";
        }
    }
}

void Client::run_qt(int argc, char **argv){
    bool keepInput = true;
    while (keepInput){
        try {
            GameConfig gameConfig;
            {
                QApplication app(argc, argv);
                Login login(keepInput, gameConfig);
                login.run();
                app.exec();
            }
            // Esto magicamente arregla parte de los bugs de QT.
            std::setlocale(LC_NUMERIC,"C");
            if (keepInput == false){
                break;
            }
            if (! gameConfig.is_well_config()){
                continue;
            }
            Game game = std::move(gameConfig.create_game());
            PlayResult playResult = game();
            {
                QApplication app(argc, argv);
                GameOver gameOver(playResult);
                gameOver.show();
                app.exec();
            }
            std::setlocale(LC_NUMERIC,"C");
        } catch (SocketException &except) {
            std::cout << "Connection Lost at C.\n";
        }
    }
}
