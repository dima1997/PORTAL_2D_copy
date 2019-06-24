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

typedef enum game_state {WAITING, READY, PLAYING, FINISHED, ERROR} game_state_t;

class Game {
    std::list<Player> players;
    std::thread thread;
    Map map;
    World world;
    ThreadSafeQueue<std::unique_ptr<GameAction>> inQueue;
    game_state_t gameState;
    void start();
    void manageActions(std::unique_ptr<GameAction> ptrAction);
    bool readyToStart();
    uint8_t getNumberOfPlayers();
public:
    Game(Connector &connector, uint8_t mapId);
    ~Game();
    void join();
    void addPlayer(Connector &connector);
    void operator()();
    game_state_t getState();
};


#endif //PORTAL_GAME_H
