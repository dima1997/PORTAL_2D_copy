#include "../../includes/threads/event_game_receiver_thread.h"

#include "../../includes/textures/common_texture/texture_move_change.h"

#include <protocol/event/event.h>
#include <protocol/event/player_wins_event.h>
#include <protocol/event/player_loses_event.h>
#include <protocol/event/player_dies_event.h>
#include <protocol/event/object_moves_event.h>
#include <protocol/event/object_switch_event.h>

#include <connector/connector.h>
#include <connector/socket_exception.h>
#include <protocol/protocol_code.h>
#include <thread_safe_queue.h>
#include <thread.h>


#include <iostream>

/*Recibe y procesa un evento del servidor.*/
void EventGameReceiverThread::receive_event(){
    uint8_t gameEventFromConnector;
    this->connector >> gameEventFromConnector;
    auto gameEvent = (EventType) gameEventFromConnector;
    switch (gameEvent){
        case player_wins:
            {    
                std::unique_ptr<Event> ptrEvent(
                    new PlayerWinsEvent()
                );
                this->changesQueue.push(ptrEvent);
                this->stop();
            }
            break;
        case player_loses:
            {
                std::unique_ptr<Event> ptrEvent(
                    new PlayerLosesEvent()
                );
                this->changesQueue.push(ptrEvent);
                this->stop();
            }
        case player_dies:
            {   
                uint32_t player_id_dead;
                this->connector >> player_id_dead;
                std::unique_ptr<Event> ptrEvent(
                    new PlayerDiesEvent(player_id_dead)
                );
                this->changesQueue.push(ptrEvent);
            }
            break;
        case object_moves:
            {
                std::unique_ptr<Event> ptrEvent(
                    new ObjectMovesEvent(0,0,0)
                );
                this->connector >> (*ptrEvent);
                this->changesQueue.push(ptrEvent);    
            }
            break;
        case object_switch_state:
            {
                std::unique_ptr<Event> ptrEvent(
                    new ObjectSwitchEvent()
                );
                this->connector >> (*ptrEvent);
                this->changesQueue.push(ptrEvent);
                break;
            }
    }
}

/*
PRE: Recibe una referencia a un conector (Connector &),
ya conectado con el servidor del juego.
POST: Inicializa un hilo recibidor de eventos del juego.
*/
EventGameReceiverThread::EventGameReceiverThread(
    Connector & connector, 
    ThreadSafeQueue<std::unique_ptr<Event>> & changesQueue,
    ThreadSafeQueue<ThreadStatus> & stopQueue
)
:   isDead(true),
    connector(connector), 
    changesQueue(changesQueue),
    stopQueue(stopQueue),
    mutex() {}

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
        std::cerr << "Connection Lost at EGR.\n";
        this->stop();
        ThreadStatus stop = THREAD_STOP;
        this->stopQueue.push(stop);
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