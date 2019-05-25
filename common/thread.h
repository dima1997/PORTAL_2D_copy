#ifndef THREAD_H
#define THREAD_H
#include <thread>

class Thread {
private:
    std::thread thread;

public:
    /*Inicializa un Thread*/
    Thread();
    
    /*Inicia un nuevo hilo de ejecucion*/
    void start();
    
    /*Espera a que el hilo en ejecucion termine*/
    void join();
        
    /*Ejecuta la funcion del hilo*/
    virtual void run() = 0;

    /*Detiene la ejecucion del hilo*/
    virtual void stop() = 0;
    
    /*
    Devuelve true si el hilo termino de ejectarse, 
    false en caso contrario
    */
    virtual bool is_dead() = 0;

    /*Destruye el Thread*/
    virtual ~Thread();
        
    /*Impide que se copien hilos por parametro*/
    Thread(const Thread&) = delete;

    /*Evita que se copien hilos por asignacion*/
    Thread& operator=(const Thread&) = delete;

    /*
    Mueve semanticamente los recursos de un Thread a otro,
    por parametro.
    */
    Thread(Thread&& other);
        
    /*
    Mueve semanticamente los recursos de un Thread a otro, 
    por asignacion.
    */
    Thread& operator=(Thread&& other);
};

#endif // THREAD_H
