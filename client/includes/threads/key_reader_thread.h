#ifndef KEY_READER_THREAD_H
#define KEY_READER_THREAD_H

#include "../../../common/thread.h"
#include "../../../common/blocking_queue.h"
#include "../../../common/protocol_code.h"
#include "../../../common/game_action.h"
#include "../textures/common_texture/area.h"
#include "../game/game.h"

#include <cstdint>

class KeyReaderThread : public Thread {
private:
    bool isDead;
    const Area & areaMainObject;
    BlockingQueue<GameAction> & gameActions;
    Game & game;

    /*
    PRE: Recibe un evento de sdl (SDL_Event &).
    POST: Procesa el evento recibido. 
    */
    void process_event(SDL_Event & event);

    /*
    Envia al juego la accion a realizar.
    */
    void send(GameActionName action);

public:
    /*
    PRE: Recibe un referencia constante al area (const Area &) 
    el objecto al que el lector hace referencia en cada acccion 
    leida; una cola bloqueante de punteros unicos a acciones del 
    juego (BlockingQueue<std::unique_ptr<GameAction>> &), y una 
    referencia al juego (Game &).
    POST: Inicializa un lector de eventos.
    */
    KeyReaderThread(const Area & areaMainObject, 
        BlockingQueue<GameAction> & gameActions, 
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