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
                    GameActionName quitGame = quit_game;
                    this->stop();
                    this->endQueue.push(quitGame);
                }
                break;
            case player_dies:
                {
                    GameActionName quitGame = quit_game;
                    this->stop();
                    this->endQueue.push(quitGame);
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
EventGameReceiverThread::EventGameReceiverThread(Connector & connector, 
    ThreadSafeQueue<std::unique_ptr<ObjectMovesEvent>> & changesQueue,
    BlockingQueue<GameActionName> & endQueue)
: connector(connector), changesQueue(changesQueue), endQueue(endQueue), isDead(true) {}

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
    {
        std::unique_lock<std::mutex> l(this->mutex);
        this->isDead = false;
    }
    try {
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
    std::unique_lock<std::mutex> l(this->mutex);
    if (! this->isDead){
        this->isDead = true;
        //this->connector.shutDownRD();
    }
}

/*
Devuelve true si el hilo esta muerto; 
false en caso contrario.
*/
bool EventGameReceiverThread::is_dead(){
    std::unique_lock<std::mutex> l(this->mutex);
    return this->isDead;
}