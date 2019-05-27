#include "game_sender_proxy_thread.h"

#include <thread.h>
#include <blocking_queue.h>
#include <protocol/object_moves_event.h>
#include <connector/connector.h>

#include <memory>
#include <mutex>

GameSenderProxyThread::GameSenderProxyThread(Connector & connector, 
        BlockingQueue<std::unique_ptr<ObjectMovesEvent>> & changesMade)
:   connector(connector), changesMade(changesMade), isDead(true) {}

GameSenderProxyThread::~GameSenderProxyThread() = default;

void GameSenderProxyThread::run(){
    {
        std::unique_lock<std::mutex> l(this->mutex);
        this->isDead = false;
    }
    try{
        while (! this->is_dead()){
            std::unique_ptr<ObjectMovesEvent> ptrEvent; 
            if (! this->changesMade.pop(ptrEvent)){
                break;
            }
            ObjectMovesEvent & event = (*ptrEvent);
            this->connector << event;
        }
        this->stop();
    } catch (SocketException & error){
        return;
    }
}
void GameSenderProxyThread::stop(){
    std::unique_lock<std::mutex> l(this->mutex);
    if (! this->isDead){
        this->isDead = true;
        //this->connector.shutDownWR();
    }
}

bool GameSenderProxyThread::is_dead(){
    std::unique_lock<std::mutex> l(this->mutex);
    return this->isDead;
}