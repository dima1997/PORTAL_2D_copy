//
// Created by franciscosicardi on 12/05/19.
//

#ifndef PORTAL_GAME_H
#define PORTAL_GAME_H

#include <connector/connector.h>
#include <thread.h>
#include <blocking_queue.h>
#include <thread_safe_queue.h>
//#include <protocol/protocol_code.h>
#include <protocol/game_action/game_action.h>

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
    bool isDead;
    ThreadSafeQueue<std::unique_ptr<ObjectMovesEvent>> changesMade;
    BlockingQueue<std::unique_ptr<GameAction>> changesAsk;
public:
    Game(Connector &connector, uint8_t game_id, uint8_t player_id);
    
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
