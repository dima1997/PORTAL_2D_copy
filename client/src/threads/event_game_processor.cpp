#include "../../includes/threads/event_game_processor.h"

#include "../../includes/threads/play_result.h"
#include "../../includes/window/window.h"
#include "../../includes/textures/common_texture/texture_move_change.h"
#include "../../includes/textures/common_texture/texture_switch_change.h"

#include <thread_safe_queue.h>
#include <protocol/protocol_code.h>
#include <protocol/event/event.h>
#include <protocol/event/player_wins_event.h>
#include <protocol/event/player_loses_event.h>
#include <protocol/event/player_dies_event.h>
#include <protocol/event/object_moves_event.h>
#include <protocol/event/object_switch_event.h>

#include <memory>
#include <ctime>

#define ONE_SECOND_EQ_MICRO_SECONDS 100000 

/*
PRE: Recibe un puntero unico a un evento (std::unique_ptr<Event>).
POST: Procesa el evento.
*/
ThreadStatus EventGameProcessor::process_event(std::unique_ptr<Event> ptrEvent){
    ThreadStatus status = THREAD_GO;
    switch(ptrEvent->eventType){
        case object_moves:
            {
                auto ptrAux = 
                    static_cast<ObjectMovesEvent* >(ptrEvent.release());
                std::unique_ptr<ObjectMovesEvent> ptrMovesEvent(ptrAux);
                this->process_event(std::move(ptrMovesEvent));
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
        default:
            break;
    }
    return status;
}
/*
PRE: Recibe un puntero unico a un evento de mover 
objeto (std::unique_ptr<ObjectMovesEvent>).
POST: Procesa el evento.
*/
void EventGameProcessor::process_event
(std::unique_ptr<ObjectMovesEvent> ptrMovesEvent){
    ObjectMovesEvent event = *(ptrMovesEvent);
    TextureMoveChange textureChange(event);
    textureChange.change(this->window);
}

/*
PRE: Recibe un puntero unico a un evento de switchear
un objecto (std::unique_ptr<ObjectSwitchEvent>).
POST: Procesa el evento.
*/
void EventGameProcessor::process_event
(std::unique_ptr<ObjectSwitchEvent> ptrSwitchEvent){
    ObjectSwitchEvent event = *(ptrSwitchEvent);
    TextureSwitchChange textureChange(event);
    textureChange.change(this->window);
}

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
    ThreadSafeQueue<std::unique_ptr<Event>> & fromGameQueue,
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
        std::unique_ptr<Event> ptrEvent;
        if (! this->fromGameQueue.pop(ptrEvent)){
            break;
        }
        if (this->process_event(std::move(ptrEvent)) == THREAD_STOP){
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

