#include "../../includes/threads/playing_loop_thread.h"

#include "../../includes/window/window.h"
#include "../../includes/mixer/mixer.h"

#include "../../includes/threads/key_reader.h"
#include "../../includes/threads/event_game_processor.h"

#include "../../includes/render_time.h" 

#include <thread.h>
#include <thread_safe_queue.h>
#include <blocking_queue.h>
#include <protocol/protocol_code.h>
#include <protocol/game_action/game_action.h>
#include <protocol/event/event.h>

#include <SDL2/SDL.h>

#include <mutex>
#include <ctime>
#include <chrono>
#include <vector>

#include "../../includes/window/record/output_format.h"
#include "../../includes/textures/common_texture/texture_move_change.h"

#define VIDEO_FILE_NAME "portal_video_"
#define VIDEO_FILE_END ".mp4"

/*
PRE: Recibe:
    la ventana (Window &) donde se renderizan las texturas;
    una cola segura en hilos donde se para recibir eventos del juego;
    una cola bloqueante para enviar acciones a realizar al juego;
    una cola bloquante para comunicarse con los 'referis' del juego, y
    reportar que el jugador se desea desconectar del juego.
POST: Inicializa un loop de juego (animaciones + input del usuario).
*/
PlayingLoopThread::PlayingLoopThread(
    ThreadSafeQueue<std::unique_ptr<TextureChange>> & fromGameQueue,
    BlockingQueue<std::unique_ptr<GameAction>> & toGameQueue,
    Window & window,
    Mixer & mixer,
    PlayResult & playResult,
    ThreadSafeQueue<ThreadStatus> & stopQueue,
    BlockingQueue<std::vector<char>> & videoFramesQueue
)
:   isDead(true),
    fromGameQueue(fromGameQueue), 
    toGameQueue(toGameQueue),
    window(window), 
    mixer(mixer),
    playResult(playResult),
    stopQueue(stopQueue),
    videoFramesQueue(videoFramesQueue),
    mutex() {}

/*
Destruye el hilo: loop de juego. 
*/
PlayingLoopThread::~PlayingLoopThread() {
    if (! this->is_dead()){
        this->stop();
    }
}

/*
Ejecuta el hilo: loop de juego.
Corre el loop de animaciones, y de lectura de input del usuario.
*/
void PlayingLoopThread::run(){
    {
        std::unique_lock<std::mutex> l(this->mutex);
        this->isDead = false;
    }

    // Inicializa procesardor de eventos del usuario.
    KeyReader keyReader(this->window,
                        this->mixer,
                        this->toGameQueue
                        );

    // Inicializa procesador de eventos del juego.
    EventGameProcessor eventProcessor(this->window, 
                                      this->fromGameQueue,
                                      this->playResult,
                                      keyReader
                                      );
    unsigned t0, t1;
    double timeWaitMicroSeconds = FRAME_TIME_WAIT_MICRO_SECONDS;
    while( ! this->is_dead() ){
        t0=clock();

        // Proceso eventos del usuario
        if (keyReader.process_some_events() == THREAD_STOP){
            break;
        }

        // Proceso eventos del juego.
        if (eventProcessor.process_some_events(timeWaitMicroSeconds) 
            == THREAD_STOP){
            break;
        }

        //Renderiza texturas
        std::vector<char> videoFrameBuffer;
        this->window.render(videoFrameBuffer);
        if (this->window.is_recording()){
            this->videoFramesQueue.push(videoFrameBuffer);
        }

        //Reproduce sonidos
        this->window.sound(this->mixer);
        
        t1 = clock();

        //Espero un tiempo entre renderizacion y renderizacion
        double timeSpendMicroSeconds = 
            (double(t1-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        std::this_thread::sleep_for(std::chrono::microseconds(
            (int)(timeWaitMicroSeconds - timeSpendMicroSeconds)
        ));

        // Verifico el estado de los otros hilos.
        ThreadStatus status;
        if (this->stopQueue.pop(status)){
            if (status == THREAD_STOP){
                break;
            }
        }
    }
    this->stop();
}

/*
Detiene el hilo: loop de juego.
*/
void PlayingLoopThread::stop(){
    std::unique_lock<std::mutex> l(this->mutex);
    this->isDead = true;
}

/*
Devuelve true, si el hilo esta muerto; false en caso contrario.
*/
bool PlayingLoopThread::is_dead(){
    std::unique_lock<std::mutex> l(this->mutex);
    return this->isDead;
} 
