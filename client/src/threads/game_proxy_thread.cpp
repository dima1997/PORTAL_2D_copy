#include "../../includes/threads/game_proxy_thread.h"

#include <SDL2/SDL.h>

#include <ctime>
#include <map>

#define METERS_MOVE 0.1
#define TIME_WAIT_MILI_SECONDS 75

/*
PRE: Recibe un mapa de ids asociados al area del mapa del juego que ocupa
su determinado objeto que representan; un cola bloqueante (TSQueueChangesAsk_t)
de cambio solicitados al juego, y una cola bloqueante (TSQueueChangesMade_t) 
de cambios realizados por el juego.
POST: Inicializa un hilo proxy de juego.
*/
GameProxyThread::GameProxyThread(std::map<uint32_t,Area> & gameMap,  
                                    TSQueueChangesMade_t & changesMade, 
                                    TSQueueChangesAsk_t & changesAsk)
: gameMap(gameMap), changesMade(changesMade), changesAsk(changesAsk), 
isDead(true) {}

/*Destruye el hilo de juego proxy juego*/
GameProxyThread::~GameProxyThread(){}

/*Ejecuta un juego proxy.*/
void GameProxyThread::run(){
    this->isDead = false;
    double timeWaitMiliSeconds = TIME_WAIT_MILI_SECONDS;
    unsigned t0,t1,t2;
    while (! this->is_dead()){
        t0 = clock();
        t2 = clock();
        double timeProcessMiliSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * 1000;
        while (! (timeProcessMiliSeconds > timeWaitMiliSeconds) ){
            std::pair<uint32_t,gameObjectAction_t> idAction;
            if (! changesAsk.pop(idAction)){
                break;
            }
            uint32_t id = idAction.first;
            gameObjectAction_t action = idAction.second;
            Area & areaOfId = this->gameMap[id];
            float xArea = areaOfId.getX();
            switch (action){
                case MOVE_LEFT:
                    areaOfId.setX(xArea - METERS_MOVE);
                    break;
                case MOVE_RIGHT:
                    areaOfId.setX(xArea + METERS_MOVE);
                    break;
            }
            std::unique_ptr<ObjectMovesEvent> ptrChange(new ObjectMovesEvent(id, areaOfId.getX(), areaOfId.getY()));
            this->changesMade.push(ptrChange);
            t1 = clock();
            timeProcessMiliSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * 1000;
        }
        t1 = clock();
        double timeSpendMiliSeconds = (double(t1-t0)/CLOCKS_PER_SEC) * 1000;
        SDL_Delay(timeWaitMiliSeconds - timeSpendMiliSeconds);
    }
}

/*Detiene la ejecucion del hilo*/
void GameProxyThread::stop(){
    this->isDead = true;
}

/*Devuelve true si el hilo esta muerto, false en caso contrario*/
bool GameProxyThread::is_dead(){
    return this->isDead;
}