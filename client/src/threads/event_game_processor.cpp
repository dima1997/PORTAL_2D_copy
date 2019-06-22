#include "../../includes/threads/event_game_processor.h"

#include "../../includes/threads/play_result.h"
#include "../../includes/window/window.h"
#include "../../includes/textures/common_texture/texture_change.h"
#include "../../includes/textures/common_texture/texture_move_change.h"
#include "../../includes/textures/common_texture/texture_switch_change.h"
#include "../../includes/textures/common_texture/portal_move_change.h"
#include "../../includes/textures/common_texture/start_follow_change.h"
#include "../../includes/textures/common_texture/stop_follow_change.h"
#include "../../includes/textures/common_texture/player_dies_change.h"
#include "../../includes/textures/common_texture/player_wins_change.h"
#include "../../includes/textures/common_texture/player_loses_change.h"

#include <thread_safe_queue.h>
#include <protocol/protocol_code.h>
// #include <protocol/event/event.h>
// #include <protocol/event/player_wins_event.h>
// #include <protocol/event/player_loses_event.h>
// #include <protocol/event/player_dies_event.h>
// #include <protocol/event/object_moves_event.h>
// #include <protocol/event/portal_moves_event.h>
// #include <protocol/event/object_switch_event.h>
// #include <protocol/event/grab_rock_event.h>
// #include <protocol/event/throw_rock_event.h>

#include <memory>
#include <ctime>

#define ONE_SECOND_EQ_MICRO_SECONDS 100000 

/*
PRE: Recibe un puntero unico a un evento (std::unique_ptr<Event>).
POST: Procesa el evento.
*/
ThreadStatus EventGameProcessor::process_event(std::unique_ptr<TextureChange> ptrChange){
    ThreadStatus status = THREAD_GO;
    ptrChange->change(this->window);
    ptrChange->change(this->playResult);
    if (this->playResult.get_game_status() != NOT_FINISHED){
        status = THREAD_STOP;
    }
    /*
    switch(ptrEvent->eventType){
        case object_moves:
            {
                auto ptrAux = 
                    static_cast<ObjectMovesEvent* >(ptrEvent.release());
                std::unique_ptr<ObjectMovesEvent> ptrMovesEvent(ptrAux);
                this->process_event(std::move(ptrMovesEvent));
            }
            break;
        case portal_moves:
            {
                auto ptrAux = 
                    static_cast<PortalMovesEvent* >(ptrEvent.release());
                std::unique_ptr<PortalMovesEvent> ptrPortalMovesEvent(ptrAux);
                this->process_event(std::move(ptrPortalMovesEvent));
            }
            break;
        case object_switch_state:
            {
                auto ptrAux = 
                    static_cast<ObjectSwitchEvent* >(ptrEvent.release());
                std::unique_ptr<ObjectSwitchEvent> ptrSwitchEvent(ptrAux);
                this->process_event(std::move(ptrSwitchEvent));
            }
            break;
        case player_wins:
            {
                this->playResult.setGameStatus(WON);
                status = THREAD_STOP;
            }
            break;
        case player_loses:
            {
                this->playResult.setGameStatus(LOST);
                status = THREAD_STOP;
            }
            break;
        case player_dies:
            {
                auto ptrAux = 
                        static_cast<PlayerDiesEvent* >(ptrEvent.release());
                    std::unique_ptr<PlayerDiesEvent> ptrDiesEvent(ptrAux);
                uint32_t playerId = ptrDiesEvent->get_id();
                this->playResult.setPlayerStatus(playerId, DEAD);
                this->window.switch_texture(playerId);
            }
            break;
        case grab_rock:
            {
                auto ptrAux = 
                        static_cast<GrabRockEvent* >(ptrEvent.release());
                std::unique_ptr<GrabRockEvent> ptrGrabEvent(ptrAux);
                uint32_t chellId = ptrGrabEvent->getChellId();
                uint32_t rockId = ptrGrabEvent->getRockId();
                this->window.start_follow(rockId, chellId);
            }
            break;
        case throw_rock:
            {
                auto ptrAux = 
                        static_cast<ThrowRockEvent* >(ptrEvent.release());
                std::unique_ptr<ThrowRockEvent> ptrThrowEvent(ptrAux);
                uint32_t rockId = ptrThrowEvent->getRockId();
                this->window.stop_follow(rockId);
            }
            break;
        default:
            break;
    }
    */
    return status;
}
/*
PRE: Recibe un puntero unico a un evento de mover 
objeto (std::unique_ptr<ObjectMovesEvent>).
POST: Procesa el evento.
*/
/*
void EventGameProcessor::process_event
(std::unique_ptr<ObjectMovesEvent> ptrMovesEvent){
    ObjectMovesEvent event = *(ptrMovesEvent);
    TextureMoveChange textureChange(event);
    textureChange.change(this->window);
}
*/
/*
void EventGameProcessor::process_event
(std::unique_ptr<PortalMovesEvent> ptrPortalMovesEvent){
    PortalMovesEvent event = *(ptrPortalMovesEvent);
    uint32_t portalId = ptrPortalMovesEvent->getId();
    float xPos = ptrPortalMovesEvent->getX();
    float yPos = ptrPortalMovesEvent->getY();
    uint32_t chellId = ptrPortalMovesEvent->get_chell_id();
    this->window.move_texture(portalId,xPos,yPos);
    this->window.point_texture(chellId,xPos,yPos);
}
*/

/*
PRE: Recibe un puntero unico a un evento de switchear
un objecto (std::unique_ptr<ObjectSwitchEvent>).
POST: Procesa el evento.
*/
/*
void EventGameProcessor::process_event
(std::unique_ptr<ObjectSwitchEvent> ptrSwitchEvent){
    ObjectSwitchEvent event = *(ptrSwitchEvent);
    TextureSwitchChange textureChange(event);
    textureChange.change(this->window);
}
*/
/*
PRE: Recibe: 
    una ventana donde se encuentran las texturas
    de los objetos a los cuales los eventos del juego 
    afectan;
    una cola segura en hilos, de donde extraer el 
    proximo evento a ejecutar;
    un tiempo (int) maximo de procesamiento, que superado
    se deja de procesar. 
*/
EventGameProcessor::EventGameProcessor(
    Window & window, 
    ThreadSafeQueue<std::unique_ptr<TextureChange>> & fromGameQueue,
    PlayResult & playResult
)
:   window(window), 
    fromGameQueue(fromGameQueue),
    playResult(playResult) {}

/*Destruye el procesador de eventos del juego.*/
EventGameProcessor::~EventGameProcessor() = default;

/*
PRE: Recibe un tiempo maximo de procesamiento de eventos 
(en microsegundos)(int).
POST: Procesa eventos del juego durante el tiempo indicado
o hasta que no hay mas eventos que procesar.
*/
ThreadStatus EventGameProcessor::process_some_events
(int timeMaxProcessMicroSeconds){
    ThreadStatus status = THREAD_GO;
    unsigned t0, t1;
    t0 = clock();
    double timeSpendMicroSeconds = 0;
    while (timeSpendMicroSeconds < timeMaxProcessMicroSeconds){
        std::unique_ptr<TextureChange> ptrChange;
        if (! this->fromGameQueue.pop(ptrChange)){
            break;
        }
        if (this->process_event(std::move(ptrChange)) == THREAD_STOP){
            status = THREAD_STOP;
            break;
        }
        t1 = clock();
        double timeSpendSeconds = (double(t1-t0)/CLOCKS_PER_SEC); 
        timeSpendMicroSeconds = 
            timeSpendSeconds * ONE_SECOND_EQ_MICRO_SECONDS;
    }
    return status;
}

