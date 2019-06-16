//
// Created by franciscosicardi on 12/05/19.
//

#ifndef PORTAL_GAME_H
#define PORTAL_GAME_H

#include <connector/connector.h>
#include <thread.h>
#include <blocking_queue.h>
#include <thread_safe_queue.h>
#include <protocol/game_action/game_action.h>
#include <protocol/event/event.h>

#include <mutex>
#include <condition_variable>
#include <vector>

class Game {
private:
    bool isDead;
    Connector connector;
    uint8_t gameId;
    uint32_t  playerId;
    uint8_t mapId;
    std::vector<std::unique_ptr<Thread>> threads;
    ThreadSafeQueue<std::unique_ptr<Event>> changesMade;
    BlockingQueue<std::unique_ptr<GameAction>> changesAsk;
    ThreadSafeQueue<ThreadStatus> stopQueue;
    BlockingQueue<std::vector<char>> videoFramesQueue;
    std::mutex mutex;
public:
    Game(Connector &connector, uint8_t game_id,
         uint32_t player_id, uint8_t mapId);
    
    /*
    PRE: Recibe un doble referencia a otra juego (Game &&).
    POST: Inicializa un nuevo juego por movimiento semantico.
    */
    Game(Game && other);

    void operator()();
    
    /*Ejecuta el juego.*/
    void run();

    /*Detiene la ejecucion del juego.*/
    void stop();

    /*Devuelve true si el hilo esta muerto.*/
    bool is_dead();
};

#endif //PORTAL_GAME_H
