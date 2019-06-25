#include "../../includes/threads/event_game_processor.h"

#include "../../includes/threads/play_result.h"
#include "../../includes/threads/key_reader.h"
#include "../../includes/window/window.h"
#include "../../includes/window/changes/change.h"

#include <thread_safe_queue.h>
#include <protocol/protocol_code.h>

#include <memory>
#include <ctime>

#define ONE_SECOND_EQ_MICRO_SECONDS 100000 

/*
PRE: Recibe un puntero unico a un evento (std::unique_ptr<Event>).
POST: Procesa el evento.
*/
ThreadStatus EventGameProcessor::process_event(std::unique_ptr<Change> ptrChange){
    ThreadStatus status = THREAD_GO;
    ptrChange->change(this->window, this->playResult, this->keyReader);
    if (this->playResult.get_game_status() != GAME_STATUS_NOT_FINISHED){
        status = THREAD_STOP;
    }
    return status;
}

/*
PRE: Recibe: 
    una ventana donde se encuentran las texturas
    de los objetos a los cuales los cambios del juego 
    afectan;
    una cola segura en hilos, de donde extraer el 
    proximo cambios a ejecutar;
    el resultado del juego;
    y el lector de eventos del usuario.
*/
EventGameProcessor::EventGameProcessor(
    Window & window, 
    ThreadSafeQueue<std::unique_ptr<Change>> & fromGameQueue,
    PlayResult & playResult,
    KeyReader & keyReader
)
:   window(window), 
    fromGameQueue(fromGameQueue),
    playResult(playResult),
    keyReader(keyReader) {}

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
        std::unique_ptr<Change> ptrChange;
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

