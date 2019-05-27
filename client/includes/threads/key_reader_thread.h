#ifndef KEY_READER_THREAD_H
#define KEY_READER_THREAD_H

#include "../textures/common_texture/area.h"
#include "../game/game.h"
#include "../window/window.h"

#include <thread.h>
#include <blocking_queue.h>
#include <protocol/protocol_code.h>
#include <protocol/game_action/game_action.h>

#include <SDL2/SDL.h>
#include <cstdint>
#include <mutex>


class KeyReaderThread : public Thread {
private:
    bool isDead;
    Window & window;
    BlockingQueue<std::unique_ptr<GameAction>> & gameActions;
    BlockingQueue<GameActionName> & endQueue;
    std::mutex mutex;

    /*
    PRE: Recibe un evento de sdl (SDL_Event &).
    POST: Procesa el evento recibido. 
    */
    void process_event(SDL_Event & event);

    /*
    PRE: Recibe el nombre de una accion del juego 
    (GamaActionName).
    POST: Encola en la cola de acciones del juego, 
    la accion correspondiente al nombre de accion 
    recibido.
    */
    void push_action(GameActionName actionName);

public:
    /*
    PRE: Recibe un referencia a la ventana donde se realizan las 
    animaciones el objecto al que el lector hace referencia en 
    cada acccion leida; una cola bloqueante de punteros unicos a 
    acciones del juego (BlockingQueue<std::unique_ptr<GameAction>> &), 
    y una cola bloqueante por donde indicarle al juego que se quiere 
    salir del mismo.
    POST: Inicializa un lector de eventos.
    */
    KeyReaderThread(Window & window, 
        BlockingQueue<std::unique_ptr<GameAction>> & gameActions, 
        BlockingQueue<GameActionName> & endQueue);

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