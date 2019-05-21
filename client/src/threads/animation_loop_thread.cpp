#include "animation_loop_thread.h"

#include "blocking_queue_changes.h"
#include "../../../common/thread.h"
#include "../window/window.h"

#include <SDL2/SDL.h>

#define TIME_WAIT_MILI_SECONDS 75

/*
PRE: Recibe donde ventana (Window &) donde se renderizan las texturas; 
y una cola bloqueante de cambios a realizar sobre las texturas de la 
ventana (blockingQueueChanges_t &).
POST: Inicializa un loop de animaciones.
*/
AnimationLoopThread::AnimationLoopThread(Window &window, 
blockingQueueChangesMade_t & changesMade)
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
    this->isDead = false;
    unsigned t0, t1, t2;
    double timeWaitMiliSeconds = TIME_WAIT_MILI_SECONDS;
    while( ! this->is_dead() ){
        t0=clock();
        t2=clock();
        double timeProcessMiliSeconds = (double(t1-t0)/CLOCKS_PER_SEC) * 1000;
        while (! timeProcessMiliSeconds > timeWaitMiliSeconds ){
            std::unique_ptr<TextureMoveChange> ptrChange;
            if (! this->changesMade.pop(ptrChange)){
                break;
            }
            TextureMoveChange change = *(ptrChange);
            change.change(this->window);
            t2=clock();
            timeProcessMiliSeconds = (double(t1-t0)/CLOCKS_PER_SEC) * 1000;
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
    //Debo o no debo poner mutex aqui ?
    this->isDead = true;
}

/*
Devuelve true, si el hilo: loop de animaciones 
esta muerto; false en caso contrario.
*/
bool AnimationLoopThread::is_dead(){
    //Debo o no debo poner mutex aqui ?
    return this->isDead;
}
