#include "game_proxy_thread.h"

#include "game_sender_proxy_thread.h"
#include "game_receiver_proxy_thread.h"

#include <thread_safe_queue.h>
#include <blocking_queue.h>
#include <thread.h>
#include <connector/connector.h>
#include <protocol/protocol.h>

#include <cstdint>
#include <mutex>
#include <thread> // de STL
#include <chrono>
#include <ctime>

#define METERS_MOVE 0.1
#define TIME_WAIT_MILI_SECONDS 75

GameProxyThread::GameProxyThread(Connector & connector, uint32_t idChell, 
                                 float xChell, float yChell)
:   connector(connector), idChell(idChell), 
    xChell(xChell), yChell(yChell), isDead(true) {}

/*Destruye el hilo de juego proxy juego*/
GameProxyThread::~GameProxyThread(){}

/*Ejecuta un juego proxy.*/
void GameProxyThread::run(){
    ThreadSafeQueue<GameActionName> changesAsk;
    BlockingQueue<std::unique_ptr<ObjectMovesEvent>> changesMade;
    {
        std::unique_lock<std::mutex> l(this->mutex);
        this->threads.push_back(std::move(std::unique_ptr<Thread>(new GameReceiverProxyThread(this->connector, changesAsk))));
        this->threads.push_back(std::move(std::unique_ptr<Thread>(new GameSenderProxyThread(this->connector, changesMade))));
        for (int i = 0; i < this->threads.size();++i){
            (*(this->threads[i])).start();
        }
        this->isDead = false;
    }
    double timeWaitMiliSeconds = TIME_WAIT_MILI_SECONDS;
    unsigned t0,t1,t2;
    while (! this->is_dead()){
        t0 = clock();
        t2 = clock();
        double timeProcessMiliSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * 1000;
        while ((! (timeProcessMiliSeconds > timeWaitMiliSeconds)) && (! this->is_dead())){
            GameActionName actionName;
            if (! this->changesAsk.pop(actionName)){
                break;
            }
            switch (actionName){
                case move_left:
                    this->xChell -= METERS_MOVE;
                    break;
                case move_right:
                    this->xChell += METERS_MOVE;
                    break;
                case quit_game:
                    this->stop();
                    continue;
            }
            std::unique_ptr<ObjectMovesEvent> ptrEvent(new ObjectMovesEvent(this->idChell, this->xChell, this->yChell));
            this->changesMade.push(ptrEvent);
            t2 = clock();
            timeProcessMiliSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * 1000;
        }
        t1 = clock();
        double timeSpendMiliSeconds = (double(t1-t0)/CLOCKS_PER_SEC) * 1000;
        std::this_thread::sleep_for(std::chrono::miliseconds(timeWaitMiliSeconds - timeSpendMiliSeconds));
    }
    this->stop();
}

/*Detiene la ejecucion del hilo*/
void GameProxyThread::stop(){
    std::unique_lock<std::mutex> l(this->mutex);
    for (int i = 0; i < this->threads.size(); ++i){
        (*(this->threads[i])).stop();
        (*(this->threads[i])).join();
    }
    this->isDead = true;
}

/*Devuelve true si el hilo esta muerto, false en caso contrario*/
bool GameProxyThread::is_dead(){
    std::unique_lock<std::mutex> l(this->mutex);
    return this->isDead;
}