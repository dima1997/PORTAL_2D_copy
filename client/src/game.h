//
// Created by franciscosicardi on 12/05/19.
//

#ifndef PORTAL_GAME_H
#define PORTAL_GAME_H


#include "../../common/connector.h"

class Game {
private:
    Connector connector;
    uint8_t gameId;
    uint8_t  playerId;
public:
    Game(Connector &connector, uint8_t game_id, uint8_t player_id);
};


#endif //PORTAL_GAME_H
