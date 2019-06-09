#ifndef PLAYING_LOOP_THREAD_H
#define PLAYING_LOOP_THREAD_H

#include "../window/window.h"
#include "../mixer/mixer.h"

#include <thread.h>
#include <thread_safe_queue.h>
#include <blocking_queue.h>
#include <protocol/protocol_code.h>
#include <protocol/event/event.h>
#include <protocol/game_action/game_action.h>
#include <mutex>

class PlayingLoopThread : public Thread {
private:
    bool isDead;
    Window & window;
    ThreadSafeQueue<std::unique_ptr<Event>> & fromGameQueue;
    BlockingQueue<std::unique_ptr<GameAction>> & toGameQueue;
    BlockingQueue<GameActionName> & talkRefereeQueue;
    Mixer & mixer;

    std::mutex mutex;
public:
    /*
    PRE: Recibe:
        la ventana (Window &) donde se renderizan las texturas;
        una cola segura en hilos donde se para recibir eventos del juego;
        una cola bloqueante para enviar acciones a realizar al juego;
        una cola bloquante para comunicarse con los 'referis' del juego, y
        reportar que el jugador se desea desconectar del juego.
    POST: Inicializa un loop de juego (animaciones + input del usuario).
    */
    PlayingLoopThread(Window &window, 
        ThreadSafeQueue<std::unique_ptr<Event>> & fromGameQueue,
        BlockingQueue<std::unique_ptr<GameAction>> & toGameQueue,
        BlockingQueue<GameActionName> & talkRefereeQueue,
        Mixer & mixer
        );
    
    /*
    Destruye el hilo: loop de juego. 
    */
    ~PlayingLoopThread();
    
    /*
    Ejecuta el hilo: loop de juego.
    Corre el loop de animaciones, y de lectura de input del usuario.
    */
    virtual void run();
    
    /*
    Detiene el hilo: loop de juego.
    */
    virtual void stop();

    /*
    Devuelve true, si el hilo esta muerto; false en caso contrario.
    */
    virtual bool is_dead();
};

#endif // PLAYING_LOOP_THREAD_H
