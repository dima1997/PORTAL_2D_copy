#ifndef PORTAL_GAME_H
#define PORTAL_GAME_H

#include "../threads/play_result.h"
#include "../window/changes/change.h"

#include <connector/connector.h>
#include <thread.h>
#include <blocking_queue.h>
#include <thread_safe_queue.h>
#include <protocol/game_action/game_action.h>
#include <protocol/event/event.h>

#include <vector>
#include <mutex>

class Game {
private:
    Connector connector;
    uint8_t gameId;
    uint32_t  playerId;
    std::string mapYaml;
    std::vector<std::unique_ptr<Thread>> threads;
    ThreadSafeQueue<std::unique_ptr<Change>> changesMade;
    BlockingQueue<std::unique_ptr<GameAction>> changesAsk;
    ThreadSafeQueue<ThreadStatus> stopQueue;
    BlockingQueue<std::vector<char>> videoFramesQueue;
    std::mutex mutex;

public:
    /*
    PRE: Recibe:
        un connector en comunicacion con el servidor del juego;
        el id del juego;
        el id del jugador principal del juego;
        un mapa de juego;
    POST: Inicializa un juego.
    */
    Game(Connector &connector, uint8_t game_id,
         uint32_t player_id, std::string & mapYaml);
    
    /*
    PRE: Recibe un doble referencia a otra juego (Game &&).
    POST: Inicializa un nuevo juego por movimiento semantico.
    */
    Game(Game && other);

    /*Ejecuta el juego.*/
    PlayResult operator()();

    /*Detiene la ejecucion del juego.*/
    void stop();
};

#endif //PORTAL_GAME_H
