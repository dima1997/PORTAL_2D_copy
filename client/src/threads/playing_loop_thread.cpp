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

//#define TIME_WAIT_MICRO_SECONDS 50000
//#define ONE_SECOND_EQ_MICRO_SECONDS 100000 

/*
PRE: Recibe:
    la ventana (Window &) donde se renderizan las texturas;
    una cola segura en hilos donde se para recibir eventos del juego;
    una cola bloqueante para enviar acciones a realizar al juego;
    una cola bloquante para comunicarse con los 'referis' del juego, y
    reportar que el jugador se desea desconectar del juego.
POST: Inicializa un loop de juego (animaciones + input del usuario).
*/
PlayingLoopThread::PlayingLoopThread(Window &window, 
ThreadSafeQueue<std::unique_ptr<Event>> & fromGameQueue,
BlockingQueue<std::unique_ptr<GameAction>> & toGameQueue,
BlockingQueue<GameActionName> & talkRefereeQueue,
Mixer & mixer)
:   isDead(true),
    window(window), 
    fromGameQueue(fromGameQueue), 
    toGameQueue(toGameQueue),
    talkRefereeQueue(talkRefereeQueue),
    mixer(mixer) {}

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
    EventGameProcessor eventProcessor(this->window, this->fromGameQueue);
    KeyReader keyReader(this->window, 
                        this->toGameQueue, 
                        this->talkRefereeQueue);
    unsigned t0, t1;//, t2;
    //double timeWaitMicroSeconds = TIME_WAIT_MICRO_SECONDS;
    double timeWaitMicroSeconds = FRAME_TIME_WAIT_MICRO_SECONDS;
    //double timeProcessMicroSeconds = FRAME_TIME_WAIT_MICRO_SECONDS;
    while( ! this->is_dead() ){
        t0=clock();
        if (keyReader.process_some_events() == quit_game){
            this->stop();
            break;
        }
        eventProcessor.process_some_events(timeWaitMicroSeconds);
        /*
        t2 = clock();
        double timeProcessMicroSeconds = 
            (double(t2-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        std::this_thread::sleep_for(std::chrono::microseconds(
            (int)(timeWaitMicroSeconds - timeSpendMicroSeconds)
        ));
        */
        //window.fill();
        window.render();
        window.sound(this->mixer);
        t1 = clock();
        double timeSpendMicroSeconds = 
            (double(t1-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        std::this_thread::sleep_for(std::chrono::microseconds(
            (int)(timeWaitMicroSeconds - timeSpendMicroSeconds)
        ));
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
