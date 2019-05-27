#ifndef GAME_PROXY_THREAD_H
#define GAME_PROXY_THREAD_H

#include <thread.h>
#include <connector/connector.h>
#include <thread_safe_queue.h>
#include <blocking_queue.h>
#include <protocol/protocol_code.h>

#include <cstdint>
#include <mutex>
#include <vector>

class GameProxyThread : public Thread{
private:
    Connector & connector;
    uint32_t idChell;
    float xChell;
    float yChell;
    bool isDead;
    std::mutex mutex;
    std::vector<std::unique_ptr<Thread>> threads;
    ThreadSafeQueue<GameActionName> changesAsk;
    BlockingQueue<std::unique_ptr<ObjectMovesEvent>> changesMade;
public:
    GameProxyThread(Connector & connector, uint32_t idChell, float xChell, float yChell);
    
    /*Destruye el hilo de juego proxy juego*/
    ~GameProxyThread();

    /*Ejecuta un juego proxy.*/
    virtual void run();

    /*Detiene la ejecucion del hilo*/
    virtual void stop();

    /*Devuelve true si el hilo esta muerto, false en caso contrario*/
    virtual bool is_dead();
};

#endif // GAME_PROXY_THREAD_H
