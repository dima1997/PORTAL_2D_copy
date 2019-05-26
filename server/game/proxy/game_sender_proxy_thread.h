#ifndef GAME_SENDER_PROXY_THREAD_H
#define GAME_SENDER_PROXY_THREAD_H

#include <thread.h>
#include <blocking_queue.h>
#include <protocol/object_moves_event.h>
#include <connector/connector.h>

#include <memory>
#include <mutex>

class GameSenderProxyThread : public Thread {
private:
    Connector & connector; 
    BlockingQueue<std::unique_ptr<ObjectMovesEvent>> & changesMade;
    bool isDead;
    std::mutex mutex;
public:
    GameSenderProxyThread(Connector & connector, 
        BlockingQueue<std::unique_ptr<ObjectMovesEvent>> & changesMade);
    ~GameSenderProxyThread();
    virtual void run();
    virtual void stop();
    virtual bool is_dead();
    
};

#endif // GAME_SENDER_PROXY_THREAD_H