//
// Created by franciscosicardi on 12/05/19.
//

#ifndef PORTAL_GAMEFACTORY_H
#define PORTAL_GAMEFACTORY_H


#include <string>
#include "game.h"

class GameFactory {
public:
    GameFactory();
    static Game createGame(std::string &host, std::string &port, std::string &command, uint8_t id);
};


#endif //PORTAL_GAMEFACTORY_H
