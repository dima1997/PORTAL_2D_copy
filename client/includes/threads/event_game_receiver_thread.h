#ifndef EVENT_GAME_RECEIVER_THREAD_H
#define EVENT_GAME_RECEIVER_THREAD_H

#include "../../../common/thread.h"
#include "../../../common/connector.h"
#include "../../../common/protocol_code.h"
#include "../../../common/thread_safe_queue.h"
#include "../../../common/object_move_change.h"
#include "../game/game.h"

#include <memory> 

class EventGameReceiverThread : public Thread {
private:
    Connector & connector;
    ThreadSafeQueue<std::unique_ptr<ObjectMoveChange>> & changesQueue;
    Game & game;
    bool isDead;

    /*Recibe y procesa un evento del servidor.*/
    void receive_event();
public:
    /*
    PRE: Recibe una referencia a un conector (Connector &),
    ya conectado con el servidor del juego.
    POST: Inicializa un hilo recibidor de eventos del juego.
    */
    EventGameReceiverThread(Connector & connetor, 
        ThreadSafeQueue<std::unique_ptr<ObjectMoveChange>> changesQueue);

    /*Destruye el hilo recibidor de eventos del juego*/
    ~EventGameReceiverThread();

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