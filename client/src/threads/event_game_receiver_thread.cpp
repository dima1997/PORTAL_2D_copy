#include "../../includes/threads/event_game_receiver_thread.h"

#include <connector/connector.h>
#include <protocol/protocol_code.h>
#include <thread_safe_queue.h>
#include <thread.h>


/*Recibe y procesa un evento del servidor.*/
void EventGameReceiverThread::receive_event(){
    try {
        uint8_t gameEventFromConnector;
        this->connector >> gameEventFromConnector;
        EventType gameEvent = (EventType) gameEventFromConnector;
        switch (gameEvent){
            case object_moves:
                {
                    std::unique_ptr<ObjectMovesEvent> ptrEvent(
                                        new ObjectMovesEvent(0,0,0));
                    this->connector >> (*ptrEvent);
                    this->changesQueue.push(ptrEvent);       
                }
                break;
            case player_wins:
                {    
                    this->game.stop();
                }
                break;
            case player_dies:
                {
                    this->game.stop();
                }
                break;
            case object_switch_state:
                break;
        }
    } catch (SocketException &error){
        // Se detuvo la ejecucion del hilo.
        return;
    }
}

/*
PRE: Recibe una referencia a un conector (Connector &),
ya conectado con el servidor del juego.
POST: Inicializa un hilo recibidor de eventos del juego.
*/
EventGameReceiverThread::EventGameReceiverThread(Connector & connetor, 
    ThreadSafeQueue<std::unique_ptr<ObjectMovesEvent>> & changesQueue,
    Game & game)
: connector(connector), changesQueue(changesQueue), game(game), isDead(true) {}

/*Destruye el hilo recibidor de eventos del juego*/
EventGameReceiverThread::~EventGameReceiverThread() = default;

/*
Ejecuta el hilo recibidor de eventos del juego.
Recibe eventos del servidor y los procesa.
Si los eventos generan cambios en las texturas 
del juego, los procesa y encola en la cola de 
cambios con que se inicializo.
*/
void EventGameReceiverThread::run(){
    try {
        this->isDead = false;
        while (! this->is_dead()){
            this->receive_event();
        }
    } catch (SocketException &error){
        return;
    }
}

/*
Detiene la ejecucion del hilo.
*/
void EventGameReceiverThread::stop(){
    if (! this->isDead){
        this->isDead = true;
        this->connector.shutDownRD();
    }
}

/*
Devuelve true si el hilo esta muerto; 
false en caso contrario.
*/
bool EventGameReceiverThread::is_dead(){
    return this->isDead;
}