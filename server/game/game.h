//
// Created by franciscosicardi on 09/05/19.
//

#ifndef PORTAL_GAME_H
#define PORTAL_GAME_H


#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <Box2D/Common/b2Math.h>
#include <connector/connector.h>
#include <thread_safe_queue.h>
#include "world.h"
#include "player.h"

#include <protocol/game_action/game_action.h>
#include <memory>

class Game {
private:
    int id;
    std::vector<Player> players;
    std::mutex mutex;
    std::condition_variable cv;
    bool ready;
    std::thread thread;
    // TODO: number of players should depend on a map, map should be an attribute
    int numberOfPlayers;
    World world;
    //ThreadSafeQueue<GameAction *> inQueue;
    ThreadSafeQueue<std::unique_ptr<GameAction>> inQueue;
    void start();
public:
    Game(uint8_t id, uint8_t mapId, Connector &connector);
    ~Game();
    Game(Game &&other) noexcept;
    Game &operator=(Game &&other) noexcept;
    void startIfReady();
    void join();
    bool isFinished();
    bool addPlayer(Connector &connector);
};


#endif //PORTAL_GAME_H
