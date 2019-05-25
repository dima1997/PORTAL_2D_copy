//
// Created by franciscosicardi on 12/05/19.
//

#ifndef PORTAL_GAME_H
#define PORTAL_GAME_H

#include <connector/connector.h>
//#include <thread.h>

#include <mutex>
#include <condition_variable>
#include <vector>

class Game {
private:
    Connector connector;
    uint8_t gameId;
    uint8_t  playerId;
    std::mutex mutex;
    std::condition_variable cv;
    std::vector<std::unique_ptr<Thread>> threads;
public:
    Game(Connector &connector, uint8_t game_id, uint8_t player_id);
    
    void operator()();
    
    /*Ejecuta el juego.*/
    void run();

    /*Detiene la ejecucion del juego.*/
    void stop();

    /*Devuelve true si el hilo esta muerto.*/
    bool is_dead();
};

#endif //PORTAL_GAME_H
