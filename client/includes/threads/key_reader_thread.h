#ifndef KEY_READER_THREAD_H
#define KEY_READER_THREAD_H

#include "../../../common/thread.h"
#include "../../../common/blocking_queue.h"
#include "../../../common/protocolo_code.h"

#include <cstdint>

class KeyReaderThread : public Thread {
private:
    bool isDead;
    uint32_t idObject;
    BlockingQueue<GameObjectAction> & gameActions;
    Game & game;

    /*
    PRE: Recibe un evento de sdl (SDL_Event &).
    POST: Procesa el evento recibido. 
    */
    void process_event(SDL_Event & event);

    /*
    Envia al juego la accion a realizar.
    */
    void send(GameObjectAction action);

public:
    /*Inicializa un lector de eventos.*/
    KeyReaderThread(uint32_t idObject, 
        BlockingQueue<GameObjectAction> & gameActions, 
        Game & game);

    /*Destruye el lector de eventos.*/
    ~KeyReaderThread();

    /*Ejecuta el lector de eventos.*/
    void run();

    /*Detiene la ejecucion del hilo.*/
    void stop();

    /*
    Devuelve true si el hilo esta muerto; 
    false en caso contrario.
    */
    bool is_dead();

    
};

#endif // KEY_READER_THREAD_H