#ifndef EVENT_GAME_PROCESSOR_H
#define EVENT_GAME_PROCESSOR_H

#include "../window/changes/change.h"

#include <thread_safe_queue.h>
#include <protocol/protocol_code.h>

#include <memory>

class Window;
class PlayResult;
class KeyReader;

class EventGameProcessor {
private:
    Window & window;
    ThreadSafeQueue<std::unique_ptr<Change>> & fromGameQueue;
    PlayResult & playResult;
    KeyReader & keyReader;

public:
    /*
    PRE: Recibe: 
        una ventana donde se encuentran las texturas
        de los objetos a los cuales los eventos del juego 
        afectan;
        una cola segura en hilos, de donde extraer el 
        proximo evento a ejecutar;
    */
    EventGameProcessor(
        Window & window, 
        ThreadSafeQueue<std::unique_ptr<Change>> & fromGameQueue,
        PlayResult & playResult,
        KeyReader & keyReader
    );

    /*Destruye el procesador de eventos del juego.*/
    ~EventGameProcessor();
    
    /*
    PRE: Recibe un puntero unico a un evento (std::unique_ptr<Change>).
    POST: Procesa el evento.
    */
    ThreadStatus process_event(std::unique_ptr<Change> ptrChange);

    /*
    PRE: Recibe un tiempo maximo de procesamiento de eventos 
    (en microsegundos)(int).
    POST: Procesa eventos del juego durante el tiempo indicado
    o hasta que no hay mas eventos que procesar.
    */
    ThreadStatus process_some_events(int timeMaxProcessMicroSeconds);
};

#endif // EVENT_GAME_PROCESSOR_H
