#ifndef GAME_PROXY_THREAD_H
#define GAME_PROXY_THREAD_H

#include <thread.h>
#include <connector/connector.h>

#include <cstdint>
#include <mutex>

class GameProxyThread : public Thread{
private:
    Connector & connector;
    uint32_t idChell;
    float xChell;
    float yChell;
    bool isDead;
    std::mutex mutex;
    std::vector<std::unique_ptr<Thread>> threads;
public:
    GameProxyThread(float xChell, float yChell);
    
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
