//
// Created by franciscosicardi on 09/05/19.
//

#ifndef PORTAL_GAME_LOBBY_H
#define PORTAL_GAME_LOBBY_H


#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <Box2D/Common/b2Math.h>
#include <connector/connector.h>
#include <thread_safe_queue.h>
#include "world.h"
#include "player.h"
#include "game.h"
#include "map.h"

#include <protocol/game_action/game_action.h>
#include <memory>

#include <cstdint>
#include <map>

class GameLobby {
private:
    uint8_t id;
    std::mutex mutex;
    std::condition_variable cv;
    std::unique_ptr<Game> game;
    std::string gameName;
    void startIfReady();
public:
    GameLobby(uint8_t id, uint8_t mapId, Connector &connector, std::string &gameName);
    ~GameLobby();
    GameLobby(GameLobby &&other) noexcept;
    GameLobby &operator=(GameLobby &&other) noexcept;
    bool isFinished();
    bool addPlayer(Connector &connector);
    bool isReady();
    std::string &getName();
    uint8_t getId();
};

#endif //PORTAL_GAME_LOBBY_H
