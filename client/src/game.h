//
// Created by franciscosicardi on 12/05/19.
//

#ifndef PORTAL_GAME_H
#define PORTAL_GAME_H


#include <connector/connector.h>

class Game {
private:
    Connector connector;
    uint8_t gameId;
    uint8_t  playerId;
public:
    Game(Connector &connector, uint8_t game_id, uint8_t player_id);
    void operator()();
};


#endif //PORTAL_GAME_H
