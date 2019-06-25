#ifndef EVENT_GAME_RECEIVER_THREAD_H
#define EVENT_GAME_RECEIVER_THREAD_H

#include "../window/changes/change.h"

#include <connector/connector.h>
#include <protocol/protocol_code.h>
#include <protocol/event/event.h>
#include <protocol/event/object_moves_event.h>
#include <thread_safe_queue.h>
#include <blocking_queue.h>
#include <thread.h>

#include <memory>
#include <mutex> 
#include <cstdint>

class EventGameReceiverThread : public Thread {
private:
    bool isDead;
    Connector & connector;
    ThreadSafeQueue<std::unique_ptr<Change>> & changesQueue;
    ThreadSafeQueue<ThreadStatus> & stopQueue;
    std::mutex mutex;
    bool started;

    /*Recibe y procesa un evento del servidor.*/
    void receive_event();

    /*Espera que el juego inicie.*/
    void wait_start_game();
public:
    /*
    PRE: Recibe una referencia a un conector (Connector &),
    ya conectado con el servidor del juego.
    POST: Inicializa un hilo recibidor de eventos del juego.
    */
    EventGameReceiverThread(
        Connector & connetor, 
        ThreadSafeQueue<std::unique_ptr<Change>> & changesQueue,
        ThreadSafeQueue<ThreadStatus> & stopQueue
        );

    /*Destruye el hilo recibidor de eventos del juego*/
    virtual ~EventGameReceiverThread();

    /*
    Ejecuta el hilo recibidor de eventos del juego.
    Recibe eventos del servidor y los procesa.
    Si los eventos generan cambios en las texturas 
    del juego, los procesa y encola en la cola de 
    cambios con que se inicializo.
    */
    virtual void run();

    /*
    Detiene la ejecucion del hilo.
    */
    virtual void stop();

    /*
    Devuelve true si el hilo esta muerto; 
    false en caso contrario.
    */
    virtual bool is_dead();
};

#endif // EVENT_GAME_RECEIVER_THREAD_H