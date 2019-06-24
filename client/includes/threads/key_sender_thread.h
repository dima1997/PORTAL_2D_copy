#ifndef KEY_SENDER_THREAD_H
#define KEY_SENDER_THREAD_H

#include <thread.h>
#include <protocol/protocol_code.h>
#include <protocol/game_action/game_action.h>
#include <blocking_queue.h>
#include <thread_safe_queue.h>

#include <mutex>

class Connector;

class KeySenderThread : public Thread {
private:
    bool isDead;
    Connector & connector;
    BlockingQueue<std::unique_ptr<GameAction>> & actionsBlockQueue;
    ThreadSafeQueue<ThreadStatus> & stopQueue;
    std::mutex mutex;
    
public:
    /*
    PRE: Recibe una referencia a un conector (Connector &),
    ya conectado con el servidor del juego.
    POST: Inicializa un hilo enviador de acciones del usuario 
    sobre objetos del juego.
    */
    KeySenderThread(
            Connector & connector, 
            BlockingQueue<std::unique_ptr<GameAction>> & actionsBlockQueue,
            ThreadSafeQueue<ThreadStatus> & stopQueue
            );
    /*
    Destruye un hilo enviador de acciones 
    del usuario sobre objetos del juego.
    */
    virtual ~KeySenderThread();

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
