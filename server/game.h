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
#include "../common/connector.h"

class Game {
private:
    int id;
    std::vector<Connector> players;
    std::mutex mutex;
    std::condition_variable cv;
    bool ready;
    bool finished;
    std::thread thread;
    // TODO: number of players should depend on a map, map should be an attribute
    int numberOfPlayers;
    void start();
public:
    Game(int id, Connector &connector);
    ~Game();
    Game(Game &&other) noexcept;
    Game &operator=(Game &&other) noexcept;
    void startIfReady();
    void finish();
    bool addPlayer(Connector &connector);
};


#endif //PORTAL_GAME_H
