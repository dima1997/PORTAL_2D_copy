#include "thread.h"

#include <thread>

/*Inicializa un Thread*/
Thread::Thread() {}

/*Inicia un nuevo hilo de ejecucion*/
void Thread::start() {
    thread = std::thread(&Thread::run, this);
}

/*Espera a que el hilo en ejecucion termine.*/
void Thread::join() {
    thread.join();
}

/*Destruye el Thread*/
Thread::~Thread() {}

/*
Mueve semanticamente los recursos de un Thread a otro,
por parametro.
*/
Thread::Thread(Thread&& other) {
    this->thread = std::move(other.thread);
}
    
/*
Mueve semanticamente los recursos de un Thread a otro, 
por asignacion.
*/
Thread& Thread::operator=(Thread&& other) {
    this->thread = std::move(other.thread);
    return *this;
}