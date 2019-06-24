//
// Created by franciscosicardi on 12/05/19.
//

#ifndef PORTAL_GAMEFACTORY_H
#define PORTAL_GAMEFACTORY_H

#include "game.h"

#include <string>

class GameFactory {
public:
    /*
    PRE: Recibe:
        el host (string) y el port (string) a donde conectarse;
        el comando de linea a utilizar ("new" o "join")
        y un id correspondiente en el primer caso al mapa de juego,
        y en el segundo al id de juego;
    POST: Devuelve un juego (Game)
    Levanta PortalException en caso de error.
    */
    static Game createGame(
        std::string &host, 
        std::string &port, 
        std::string &command, 
        uint8_t id
    );
};


#endif //PORTAL_GAMEFACTORY_H
