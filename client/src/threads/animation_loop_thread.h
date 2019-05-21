#ifndef ANIMATION_LOOP_THREAD_H
#define ANIMATION_LOOP_THREAD_H

#include "blocking_queue_changes.h"
#include "../window/window.h"
#include "../../../common/thread.h"

class AnimationLoopThread : public Thread{
private:
    Window & window;
    blockingQueueChangesMade_t & changesMade;
    bool isDead;
public:
    /*
    PRE: Recibe donde ventana (Window &) donde se renderizan las texturas; 
    y una cola bloqueante de cambios a realizar sobre las texturas de la 
    ventana (blockingQueueChanges_t &).
    POST: Inicializa un loop de animaciones.
    */
    AnimationLoopThread(Window &window, 
        blockingQueueChangesMade_t & changesMade);
    /*
    Destruye el hilo: loop de animaciones. 
    */
    ~AnimationLoopThread();
    /*
    Ejecuta el hilo: loop de animaciones
    */
    void run();
    /*
    Detiene el hilo: loop de animaciones.
    */
    void stop();

    /*
    Devuelve true, si el hilo: loop de animaciones 
    esta muerto; false en caso contrario.
    */
    bool is_dead();    
};


#endif // ANIMATION_LOOP_THREAD_H