//
// Created by franciscosicardi on 09/05/19.
//

#ifndef PORTAL_GAMEMANAGER_H
#define PORTAL_GAMEMANAGER_H


#include <unordered_map>
#include <cstdint>
#include <mutex>
#include "game_lobby.h"
#include <connector/connector.h>

class GameManager {
private:
    std::unordered_map<uint8_t, GameLobby> games;
    std::mutex mutex;
    uint8_t biggestKey;
    uint8_t getKey();
    void eraseFinished();
    void sendAvailableGames(Connector &connector);
public:
    GameManager();
    ~GameManager();
    void addGame(Connector &connector);
    void joinToGame(Connector &connector);
};


#endif //PORTAL_GAMEMANAGER_H
