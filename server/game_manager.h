//
// Created by franciscosicardi on 09/05/19.
//

#ifndef PORTAL_GAMEMANAGER_H
#define PORTAL_GAMEMANAGER_H


#include <unordered_map>
#include <cstdint>
#include <mutex>
#include "game.h"
#include "../common/connector/connector.h"

class GameManager {
private:
    std::unordered_map<uint8_t, Game> games;
    std::mutex mutex;
    uint8_t biggestKey;
    uint8_t getKey();
    void eraseFinished();
public:
    GameManager();
    ~GameManager();
    void addGame(Connector &connector, uint8_t mapId);
    void joinToGame(uint8_t gameId, Connector &connector);
};


#endif //PORTAL_GAMEMANAGER_H
