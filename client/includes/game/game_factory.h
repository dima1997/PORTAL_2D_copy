//
// Created by franciscosicardi on 12/05/19.
//

#ifndef PORTAL_GAMEFACTORY_H
#define PORTAL_GAMEFACTORY_H


#include "game.h"
#include <connector/connector.h>
#include <string>
#include <cstdint>

class GameFactory {
public:
    GameFactory();
    ~GameFactory();
    Game createGame(std::string &host, std::string &port, std::string &command, uint8_t id); //static 
    Game start_new_game(Connector & connector, uint8_t mapId);
    Game start_join_game(Connector & connector, uint8_t gameId);
};


#endif //PORTAL_GAMEFACTORY_H
