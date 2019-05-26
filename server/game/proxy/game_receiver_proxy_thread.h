#ifndef GAME_RECEIVER_PROXY_THREAD_H
#define GAME_RECEIVER_PROXY_THREAD_H

#include <connector/connector.h>
#include <blocking_queue.h>
#include <thread.h>
#include <protocol/protocol.h>

#include <mutex>

class GameReceiverProxyThread : public Thread {
private:
    Connector & connector; 
    ThreadSafeQueue<GameActionName> & changesAsk;
    bool isDead;
    std::mutex mutex;
public:
    GameReceiverProxyThread(Connector & connector, 
        ThreadSafeQueue<GameActionName> & changesAsk);
    
    ~GameReceiverProxyThread();
    
    virtual void run();

    virtual void stop();

    virtual bool is_dead();
};

#endif // GAME_RECEIVER_PROXY_THREAD_H
