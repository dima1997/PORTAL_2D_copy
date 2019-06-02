//
// Created by franciscosicardi on 02/06/19.
//

#ifndef PORTAL_GAME_H
#define PORTAL_GAME_H


#include <thread>
#include <thread_safe_queue.h>
#include <protocol/game_action/game_action.h>
#include "world.h"
#include "player.h"
#include "map.h"

class Game {
    std::vector<Player> players;
    std::thread thread;
    int numberOfPlayers;
    World world;
    ThreadSafeQueue<std::unique_ptr<GameAction>> inQueue;
    void start();
    void manageActions(std::unique_ptr<GameAction> ptrAction);
public:
    Game(std::vector<Connector> &vector, Map &map);
    void operator()();
    void join();
    bool isFinished();
};


#endif //PORTAL_GAME_H
