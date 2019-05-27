#ifndef ANIMATION_LOOP_THREAD_H
#define ANIMATION_LOOP_THREAD_H

#include "../window/window.h"
#include <thread.h>
#include <thread_safe_queue.h>

#include <mutex>

class AnimationLoopThread : public Thread{
private:
    Window & window;
    TSQueueChangesMade_t & changesMade;
    bool isDead;
    std::mutex mutex;
public:
    /*
    PRE: Recibe donde ventana (Window &) donde se renderizan las texturas; 
    y una cola bloqueante de cambios a realizar sobre las texturas de la 
    ventana (blockingQueueChanges_t &).
    POST: Inicializa un loop de animaciones.
    */
    AnimationLoopThread(Window &window, 
        TSQueueChangesMade_t & changesMade);
    /*
    AnimationLoopThread(Window &window, 
        queueChangesMade_t & changesMade);
    */
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
