#include "../../includes/threads/animation_loop_thread.h"

#include "../../includes/window/window.h"
#include "../../includes/textures/common_texture/texture_move_change.h"

#include <thread.h>
#include <thread_safe_queue.h>
#include <protocol/object_moves_event.h>

#include <SDL2/SDL.h>

#define TIME_WAIT_MILI_SECONDS 75

/*
PRE: Recibe donde ventana (Window &) donde se renderizan las texturas; 
y una cola bloqueante de cambios a realizar sobre las texturas de la 
ventana (TSQueueChangesMade_t &).
POST: Inicializa un loop de animaciones.
*/
AnimationLoopThread::AnimationLoopThread(Window &window, 
ThreadSafeQueue<std::unique_ptr<ObjectMovesEvent>> & changesMade)
: window(window), changesMade(changesMade), isDead(true) {}

/*
Destruye el hilo: loop de animaciones. 
*/
AnimationLoopThread::~AnimationLoopThread(){
    this->stop();
}

/*
Ejecuta el hilo: loop de animaciones
*/
void AnimationLoopThread::run(){
    {
        std::unique_lock<std::mutex> l(this->mutex);
        this->isDead = false;
    }
    unsigned t0, t1, t2;
    double timeWaitMiliSeconds = TIME_WAIT_MILI_SECONDS;
    while( ! this->is_dead() ){
        t0=clock();
        t2=clock();
        double timeProcessMiliSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * 1000;
        while (! (timeProcessMiliSeconds > timeWaitMiliSeconds) ){
            std::unique_ptr<ObjectMovesEvent> ptrEvent;
            if (! this->changesMade.pop(ptrEvent)){
                break;
            }
            ObjectMovesEvent event = *(ptrEvent);
            TextureMoveChange textureChange(event);
            textureChange.change(this->window);
            t2=clock();
            timeProcessMiliSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * 1000;
        }
        window.fill();
        window.render();
        t1 = clock();
        double timeSpendMiliSeconds = (double(t1-t0)/CLOCKS_PER_SEC) * 1000;
        SDL_Delay(timeWaitMiliSeconds - timeSpendMiliSeconds);
    }
    this->stop();
}

/*
Detiene el hilo: loop de animaciones.
*/
void AnimationLoopThread::stop(){
    std::unique_lock<std::mutex> l(this->mutex);
    this->isDead = true;
}

/*
Devuelve true, si el hilo: loop de animaciones 
esta muerto; false en caso contrario.
*/
bool AnimationLoopThread::is_dead(){
    std::unique_lock<std::mutex> l(this->mutex);
    return this->isDead;
}
