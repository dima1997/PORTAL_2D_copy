//
// Created by franciscosicardi on 09/05/19.
//

#ifndef PORTAL_GAME_H
#define PORTAL_GAME_H


#include <vector>
#include <mutex>
#include <thread>
#include "../common/connector.h"

class Game {
private:
    int id;
    std::vector<Connector> players;
    std::mutex mutex;
    bool ready;
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
    bool addPlayer(Connector &connector);
};


#endif //PORTAL_GAME_H
