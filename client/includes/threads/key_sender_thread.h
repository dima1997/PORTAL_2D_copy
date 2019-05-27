#ifndef KEY_SENDER_THREAD_H
#define KEY_SENDER_THREAD_H

#include <thread.h>
#include <connector/connector.h>
#include <protocol/protocol_code.h>
#include <blocking_queue.h>
#include <protocol/game_action/game_action.h>

#include <mutex>

class KeySenderThread : public Thread {
private:
    Connector & connector;
    BlockingQueue<std::unique_ptr<GameAction>> & actionsBlockQueue;
    bool isDead;
    std::mutex mutex;
    
public:
    /*
    PRE: Recibe una referencia a un conector (Connector &),
    ya conectado con el servidor del juego.
    POST: Inicializa un hilo enviador de acciones del usuario 
    sobre objetos del juego.
    */
    KeySenderThread(Connector & connector, 
            BlockingQueue<std::unique_ptr<GameAction>> & actionsBlockQueue);
    /*
    Destruye un hilo enviador de acciones 
    del usuario sobre objetos del juego.
    */
    ~KeySenderThread();

    /*
    Ejecuta un hilo enviador de acciones 
    del usuario sobre objetos del juego.
    */
    virtual void run();

    /*Detiene la ejecucion del hilo.*/
    virtual void stop();

    /*
    Devuelve true si el hilo esta muerto; 
    false en caso contrario.
    */
    virtual bool is_dead();
};

#endif // KEY_SENDER_THREAD_H
