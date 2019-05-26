#include "game_receiver_proxy_thread.h"

#include <connector/connector.h>
#include <blocking_queue.h>
#include <thread.h>
#include <protocol/protocol.h>

#include <mutex>

GameReceiverProxyThread::GameReceiverProxyThread(Connector & connector, 
                            ThreadSafeQueue<GameActionName> & changesAsk)
:   connector(connector), changesAsk(changesAsk), isDead(true) {}
    
GameReceiverProxyThread::~GameReceiverProxyThread() = default;
    
void run(){
    {
        std::unique_lock<std::mutex> l(this->mutex);
        this->isDead = false;
    }
    try {
        while (! this->is_dead()){
            uint8_t actionNameExplicit;
            this->connector >> actionNameExplicit;
            GameActionName actionName = (GameActionName) actionNameExplicit;
            this->changesAsk.push(actionNameExplicit);
        }
        this->stop();
    } catch (SocketException & error){
        return;
    }

}

void stop(){
    std::unique_lock<std::mutex> l(this->mutex);
    if (!this->isDead){
        this->isDead = true;
        this->connector.shutDownRD();
    }
}

bool is_dead(){
    std::unique_lock<std::mutex> l(this->mutex);
    return this->isDead;
}