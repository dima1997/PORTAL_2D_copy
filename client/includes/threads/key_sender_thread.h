#ifndef KEY_SENDER_THREAD_H
#define KEY_SENDER_THREAD_H

#include "../../../common/thread.h"
#include "../../../common/connector.h"
#include "../../../common/protocol_code.h"
#include "../../../common/blocking_queue.h" 

class KeySenderThread : public Thread {
private:
    Connector & connector;
    BlockingQueue<GameObjectAction> & actionsBlockQueue;

public:
    /*
    PRE: Recibe una referencia a un conector (Connector &),
    ya conectado con el servidor del juego.
    POST: Inicializa un hilo enviador de acciones del usuario 
    sobre objetos del juego.
    */
    KeySenderThread(Connector & connector, 
                        BlockingQueue<GameObjectAction> & actionsBlockQueue);
    /*
    Destruye un hilo enviador de acciones 
    del usuario sobre objetos del juego.
    */
    ~KeySenderThread() = default;

    /*
    Ejecuta un hilo enviador de acciones 
    del usuario sobre objetos del juego.
    */
    void run();

    /*Detiene la ejecucion del hilo.*/
    void stop();

    /*
    Devuelve true si el hilo esta muerto; 
    false en caso contrario.
    */
    bool is_dead();
};

#endif // KEY_SENDER_THREAD_H
