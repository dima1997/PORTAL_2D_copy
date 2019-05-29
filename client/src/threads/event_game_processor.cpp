#include "../../includes/threads/event_game_processor.h"

#include <ctime>

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
EventGameProcessor::EventGameProcessor(Window & Window, 
ThreadSafeQueue<std::unique_ptr<Event>> & fromGameQueue,
int timeMaxProcess)
:   window(window), 
    fromGameQueue(fromGameQueue) {}

/*Destruye el procesador de eventos del juego.*/
EventGameProcessor::EventGameProcessor() = default;

/*
PRE: Recibe un tiempo maximo de procesamiento de eventos.
POST: Procesa eventos del juego durante el tiempo indicado
o hasta que no hay mas eventos que procesar.
*/
void EventGameProcessor::process_some_events(int timeMaxProcess){
    unsigned t0, t1;
    double timeSpend = 0;
    while (timeSpend <= timeMaxProcess){
        std::unique_ptr<Event> ptrEvent;
        if (! this->fromGameQueue.pop(ptrEvent)){
            break;
        }
        this->process_event(ptrEvent);
    }
}

/*
PRE: Recibe un puntero unico a un evento (std::unique_ptr<Event>).
*/
EventGameProcessor::process_event(std::unique_ptr<Event> ptrEvent){
    switch(ptrEvent->eventType){
        case object_moves:
            {
                auto ptrAux = static_cast<ObjectMovesEvent* >(ptrEvent.release());
                std::unique_ptr<ObjectMovesEvent> ptrMovesEvent(ptrAux);
                ObjectMovesEvent event = *(ptrMovesEvent);
                TextureMoveChange textureChange(event);
                textureChange.change(this->window);
            }
            break;
        case object_switch_state:
            {
                auto ptrAux = static_cast<ObjectSwitchEvent* >(ptrEvent.release());
                std::unique_ptr<ObjectSwitchEvent> ptrSwitchEvent(ptrAux);
                ObjectSwitchEvent event = *(ptrSwitchEvent);
                TextureSwitchChange textureChange(event);
                textureChange.change(this->window);
            }
    }
}