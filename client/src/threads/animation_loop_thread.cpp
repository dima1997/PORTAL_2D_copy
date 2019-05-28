#include "../../includes/threads/animation_loop_thread.h"

#include "../../includes/textures/common_texture/texture_move_change.h"
#include "../../includes/window/window.h"
#include <protocol/event/event.h>
#include <protocol/protocol_code.h>

#include <thread.h>
#include <thread_safe_queue.h>
#include <protocol/event/object_moves_event.h>

#include <SDL2/SDL.h>

#define TIME_WAIT_MICRO_SECONDS 70000
#define ONE_SECOND_EQ_MICRO_SECONDS 100000 

/*
PRE: Recibe donde ventana (Window &) donde se renderizan las texturas; 
y una cola bloqueante de cambios a realizar sobre las texturas de la 
ventana (TSQueueChangesMade_t &).
POST: Inicializa un loop de animaciones.
*/

AnimationLoopThread::AnimationLoopThread(Window &window, 
ThreadSafeQueue<std::unique_ptr<Event>> & changesMade)
: window(window), changesMade(changesMade), isDead(true) {}

/*
AnimationLoopThread::AnimationLoopThread(Window &window, 
ThreadSafeQueue<std::unique_ptr<TextureChange>> & changesMade)
: window(window), changesMade(changesMade), isDead(true) {}
*/
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
    double timeWaitMicroSeconds = TIME_WAIT_MICRO_SECONDS;
    while( ! this->is_dead() ){
        t0=clock();
        t2=clock();
        double timeProcessMicroSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        while (timeProcessMicroSeconds <= timeWaitMicroSeconds){
            std::unique_ptr<Event> ptrEvent;
            //std::unique_ptr<TextureChange> ptrChange;
            if (! this->changesMade.pop(ptrEvent)){
            //if (! this->changesMade.pop(ptrChange)){
                break;
            }
            switch(ptrEvent->eventType){
                case object_moves:
                    {
                        auto ptrAux = static_cast<ObjectMovesEvent* >(ptrEvent.release());
                        std::unique_ptr<ObjectMovesEvent> ptrMovesEvent(ptrAux);
                        ObjectMovesEvent event = *(ptrMovesEvent);
                        TextureMoveChange textureChange(event);
                        textureChange.change(this->window);
                    }
                    break;
            }
            
            //ptrChange->change(this->window);
            t2=clock();
            timeProcessMicroSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        }
        window.fill();
        window.render();
        t1 = clock();
        double timeSpendMicroSeconds = (double(t1-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        std::this_thread::sleep_for(std::chrono::microseconds((int)(timeWaitMicroSeconds - timeSpendMicroSeconds)));
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
