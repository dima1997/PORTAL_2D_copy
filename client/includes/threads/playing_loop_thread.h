#ifndef PLAYING_LOOP_THREAD_H
#define PLAYING_LOOP_THREAD_H

#include "../window/window.h"
#include "../mixer/mixer.h"
#include "../textures/common_texture/texture_change.h"
#include "play_result.h"

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
    ThreadSafeQueue<std::unique_ptr<TextureChange>> & fromGameQueue;
    BlockingQueue<std::unique_ptr<GameAction>> & toGameQueue;
    Window & window;
    Mixer & mixer;
    PlayResult & playResult;
    ThreadSafeQueue<ThreadStatus> & stopQueue;
    BlockingQueue<std::vector<char>> & videoFramesQueue;
    std::mutex mutex;
public:
    /*
    PRE: Recibe:
        una cola segura en hilos donde se para recibir eventos del juego;
        una cola bloqueante para enviar acciones a realizar al juego;
        la ventana (Window &) donde se renderizan las texturas;
        el mixer que reproduce los sonidos del juego;
        el resultado del juego donde ir volcando estadisticas.
    POST: Inicializa un loop de juego.
    */
    PlayingLoopThread( 
        ThreadSafeQueue<std::unique_ptr<TextureChange>> & fromGameQueue,
        BlockingQueue<std::unique_ptr<GameAction>> & toGameQueue,
        Window & window,
        Mixer & mixer,
        PlayResult & playResult,
        ThreadSafeQueue<ThreadStatus> & stopQueue,
        BlockingQueue<std::vector<char>> & videoFramesQueue
    );
    
    /*
    Destruye el hilo: loop de juego. 
    */
    virtual ~PlayingLoopThread();
    
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
