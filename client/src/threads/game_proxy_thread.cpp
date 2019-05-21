#include "game_proxy_thread.h"

#include "../common_texture/texture_move_change.h"
#include "blocking_queue_changes.h"

#define METERS_MOVE 0.1

/*
PRE: Recibe un mapa de ids asociados al area del mapa del juego que ocupa
su determinado objeto que representan; un cola bloqueante (blockingQueueChanges_t)
de cambio solicitados al juego, y una cola bloqueante (blockingQueueComuncation_t) 
de cambios realizados por el juego.
POST: Inicializa un hilo proxy de juego.
*/
GameProxyThread::GameProxyThread(std::map<uint32_t,Area> & gameMap,  
                                    blockingQueueChangesMade_t & changesMade, 
                                    blockingQueueChangesAsk_t & changesAsk)
: gameMap(gameMap), changesMade(changesMade), changesAsk(changesAsk), 
isDead(true) {}

/*Destruye el hilo de juego proxy juego*/
GameProxyThread::~GameProxyThread(){}

/*Ejecuta un juego proxy.*/
void GameProxyThread::run(){
    this->isDead = false;
    while (! this->is_dead()){
        std::pair<uint32_t,gameObjectAction_t> idAction;
        if (! changesAsk.pop(idAction)){
            break;
        }
        uint32_t id = idAction.first;
        gameObjectAction_t action = idAction.second;
        Area &idArea = this->gameMap[id];
        switch (action){
            case MOVE_LEFT:
                float xArea = idArea.getX();
                idArea.setX(xArea - METERS_MOVE);
                break;
            case MOVE_RIGHT:
                float xArea = idArea.getX();
                idArea.setX(xArea + METERS_MOVE);
                break;
        }
        std::unique_ptr ptrChange(new TextureMoveChange(id, idArea.getX(), idArea.getY()));
        this->changesMade.push(ptrChange);
    }
    this->stop();
}

/*Detiene la ejecucion del hilo*/
void GameProxyThread::stop(){
    this->isDead = true;
}

/*Devuelve true si el hilo esta muerto, false en caso contrario*/
bool GameProxyThread::is_dead(){
    return this->isDead;
}