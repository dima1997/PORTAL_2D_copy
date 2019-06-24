#include "../../includes/threads/event_game_receiver_thread.h"

#include "../../includes/textures/common_texture/texture_change.h"
#include "../../includes/textures/common_texture/texture_move_change.h"
#include "../../includes/textures/common_texture/texture_switch_change.h"
#include "../../includes/textures/common_texture/portal_move_change.h"
#include "../../includes/textures/common_texture/start_follow_change.h"
#include "../../includes/textures/common_texture/stop_follow_change.h"
#include "../../includes/textures/common_texture/player_dies_change.h"
#include "../../includes/textures/common_texture/player_wins_change.h"
#include "../../includes/textures/common_texture/player_loses_change.h"
#include "../../includes/textures/common_texture/start_game_change.h"
#include "../../includes/textures/common_texture/player_reach_cake_change.h"

#include <protocol/event/event.h>
#include <protocol/event/player_wins_event.h>
#include <protocol/event/player_loses_event.h>
#include <protocol/event/player_dies_event.h>
#include <protocol/event/object_moves_event.h>
#include <protocol/event/portal_moves_event.h>
#include <protocol/event/object_switch_event.h>
#include <protocol/event/grab_rock_event.h>
#include <protocol/event/throw_rock_event.h>
#include <protocol/event/player_reach_cake_event.h>

#include <connector/connector.h>
#include <connector/socket_exception.h>
#include <protocol/protocol_code.h>
#include <thread_safe_queue.h>
#include <thread.h>
#include <portal_exception.h>

#include <iostream>
#include <sstream>

/*Recibe y procesa un evento del servidor.*/
void EventGameReceiverThread::receive_event(){
    uint8_t gameEventFromConnector;
    this->connector >> gameEventFromConnector;
    auto gameEvent = (EventType) gameEventFromConnector;
    switch (gameEvent){
        case player_wins:
            {   
                std::unique_ptr<TextureChange> ptrChange(
                    new PlayerWinsChange()
                );

                this->changesQueue.push(ptrChange);
                this->stop();
            }
            break;
        case player_loses:
            {
                std::unique_ptr<TextureChange> ptrChange(
                    new PlayerLosesChange()
                );
                this->changesQueue.push(ptrChange);
                this->stop();
            }
            break;
        case player_dies:
            {   
                uint32_t player_id_dead;
                this->connector >> player_id_dead;
                std::unique_ptr<TextureChange> ptrChange(
                    new PlayerDiesChange(player_id_dead)
                );
                this->changesQueue.push(ptrChange);
            }
            break;
        case player_reach_cake:
            {
                uint32_t player_id_cake;
                this->connector >> player_id_cake;
                std::unique_ptr<TextureChange> ptrChange(
                    new PlayerReachCakeChange(player_id_cake)
                );
                this->changesQueue.push(ptrChange);
            }
            break;
        case object_moves:
            {
                ObjectMovesEvent movesEvent;
                this->connector >> movesEvent;
                std::unique_ptr<TextureChange> ptrChange(
                    new TextureMoveChange(
                        movesEvent.getId(), 
                        movesEvent.getX(), 
                        movesEvent.getY()
                    )
                );
                this->changesQueue.push(ptrChange);    
            }
            break;
        case portal_moves:
            {
                PortalMovesEvent portalMovesEvent;
                this->connector >> portalMovesEvent;
                std::unique_ptr<TextureChange> ptrChange(
                    new PortalMoveChange(
                        portalMovesEvent.getId(),
                        portalMovesEvent.getX(),
                        portalMovesEvent.getY(),
                        portalMovesEvent.get_chell_id(),
                        portalMovesEvent.get_normal_x(),
                        portalMovesEvent.get_normal_y()
                    )
                );
                this->changesQueue.push(ptrChange);  
            }
            break;
        case object_switch_state:
            {
                ObjectSwitchEvent switchEvent;
                this->connector >> switchEvent;
                std::unique_ptr<TextureChange> ptrChange(
                    new TextureSwitchChange(switchEvent.getObjectId())
                );
                this->changesQueue.push(ptrChange);
            }
            break;
        case grab_rock:
            {   
                GrabRockEvent grabRockEvent(0,0);
                this->connector >> grabRockEvent;
                std::unique_ptr<TextureChange> ptrChange(
                    new StartFollowChange(
                        grabRockEvent.getRockId(),
                        grabRockEvent.getChellId()
                    )
                );
                this->changesQueue.push(ptrChange);
            }
            break;
        case throw_rock:
            {   
                ThrowRockEvent throwRockEvent(0);
                this->connector >> throwRockEvent;
                std::unique_ptr<TextureChange> ptrChange(
                    new StopFollowChange(throwRockEvent.getRockId())
                );
                this->changesQueue.push(ptrChange);
            }
            break;
    }
}

/*Espera que el juego inicie.*/
void EventGameReceiverThread::wait_start_game() {
    uint8_t gameEventFromConnector;
    this->connector >> gameEventFromConnector;
    auto gameEvent = (EventType) gameEventFromConnector;
    switch (gameEvent){
        case game_starts:
            {
                this->started = true;
                std::unique_ptr<TextureChange> ptrChange(
                    new StartGameChange()
                );
                this->changesQueue.push(ptrChange);
            }
            break;
        default:
            {   
                std::stringstream err;
                err << "Game could not start\n";
                throw PortalException(err.str());
            }
            break;
    }
}

/*
PRE: Recibe una referencia a un conector (Connector &),
ya conectado con el servidor del juego.
POST: Inicializa un hilo recibidor de eventos del juego.
*/
EventGameReceiverThread::EventGameReceiverThread(
    Connector & connector, 
    ThreadSafeQueue<std::unique_ptr<TextureChange>> & changesQueue,
    ThreadSafeQueue<ThreadStatus> & stopQueue
)
:   isDead(true),
    connector(connector), 
    changesQueue(changesQueue),
    stopQueue(stopQueue),
    mutex(),
    started(false) {}

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
            if (started){
                this->receive_event();
            } else {
                this->wait_start_game();
            }
        }
    } catch (SocketException & error){
        std::cerr << "Connection Lost at EGR.\n";
        return;
    } catch (PortalException & error){
        std::cerr << error.what();
    }
    if (! this->is_dead()){
        this->stop();
        ThreadStatus stop = THREAD_STOP;
        this->stopQueue.push(stop);
    }
}

/*
Detiene la ejecucion del hilo.
*/
void EventGameReceiverThread::stop(){
    std::unique_lock<std::mutex> l(this->mutex);
    if (! this->isDead){
        try {
            this->connector.shutDownRD();
        } catch (SocketException & error){}
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