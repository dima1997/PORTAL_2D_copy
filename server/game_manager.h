//
// Created by franciscosicardi on 09/05/19.
//

#ifndef PORTAL_GAMEMANAGER_H
#define PORTAL_GAMEMANAGER_H


#include <vector>
#include <cstdint>
#include <mutex>
#include "game.h"
#include "../common/connector.h"

class GameManager {
private:
    std::vector<Game> games;
    std::mutex mutex;
public:
    GameManager();
    ~GameManager();
    void addGame(Connector &connector, uint8_t mapId);
    void joinToGame(uint8_t gameId, Connector &connector);
};


#endif //PORTAL_GAMEMANAGER_H
