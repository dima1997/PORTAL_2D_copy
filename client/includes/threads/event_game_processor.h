#ifndef EVENT_GAME_PROCESSOR_H
#define EVENT_GAME_PROCESSOR_H

#include "../window/window.h"

#include <thread_safe_queue.h>
#include <protocol/event/event.h>
#include <protocol/event/object_moves_event.h>
#include <protocol/event/object_switch_event.h>

#include <memory>

class EventGameProcessor {
private:
    Window & window;
    ThreadSafeQueue<std::unique_ptr<Event>> & fromGameQueue;
    /*
    PRE: Recibe un puntero unico a un evento de mover 
    objeto (std::unique_ptr<ObjectMovesEvent>).
    POST: Procesa el evento.
    */
    void process_event(std::unique_ptr<ObjectMovesEvent> ptrMovesEvent);

    /*
    PRE: Recibe un puntero unico a un evento de switchear
    un objecto (std::unique_ptr<ObjectSwitchEvent>).
    POST: Procesa el evento.
    */
    void process_event(std::unique_ptr<ObjectSwitchEvent> ptrSwitchEvent);

public:
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
    EventGameProcessor(Window & window, 
    ThreadSafeQueue<std::unique_ptr<Event>> & fromGameQueue);

    /*Destruye el procesador de eventos del juego.*/
    ~EventGameProcessor();
    
    /*
    PRE: Recibe un puntero unico a un evento (std::unique_ptr<Event>).
    POST: Procesa el evento.
    */
    void process_event(std::unique_ptr<Event> ptrEvent);

    /*
    PRE: Recibe un tiempo maximo de procesamiento de eventos 
    (en microsegundos)(int).
    POST: Procesa eventos del juego durante el tiempo indicado
    o hasta que no hay mas eventos que procesar.
    */
    void process_some_events(int timeMaxProcessMicroSeconds);
};

#endif // EVENT_GAME_PROCESSOR_H
