#ifndef GAME_PROXY_THREAD_H
#define GAME_PROXY_THREAD_H

#include "blocking_queue_changes.h" 
#include "../common_texture/area.h"

#include <cstdint>


class GameProxyThread{
private:
    std::map<uint32_t,Area> & gameMap;
    blockingQueueChangesMade_t & changesMade;
    blockingQueueChangesAsk_t & changesAsk;
    bool isDead;
public:
    /*
    PRE: Recibe un mapa de ids asociados al area del mapa del juego que ocupa
    su determinado objeto que representan; un cola bloqueante (blockingQueueChanges_t)
    de cambio solicitados al juego, y una cola bloqueante (blockingQueueComuncation_t) 
    de cambios realizados por el juego.
    POST: Inicializa un hilo proxy de juego.
    */
    GameProxyThread(std::map<uint32_t,Area> & gameMap,  
                    blockingQueueChangesMade_t & changesMade, 
                    blockingQueueChangesAsk_t & changesAsk);

    /*Destruye el hilo de juego proxy juego*/
    ~GameProxyThread();

    /*Ejecuta un juego proxy.*/
    void run();

    /*Detiene la ejecucion del hilo*/
    void stop();

    /*Devuelve true si el hilo esta muerto, false en caso contrario*/
    bool is_dead();
};

#endif // GAME_PROXY_THREAD_H