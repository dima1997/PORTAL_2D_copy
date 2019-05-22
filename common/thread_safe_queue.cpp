#include "thread_safe_queue.h"

/*
Inicializa una cola segura en hilos de ejecucion,
no bloqueante, de elemento tipo T.
T debe implementar constructor y asignacion por 
movimiento semantico.
*/
template <class T>
ThreadSafeQueue<T>::ThreadSafeQueue(): mutex(), queue() {}

/*
Destruye un la cola segura en hilos de ejecucion,
no bloqueante. 
*/
template <class T>
ThreadSafeQueue<T>::~ThreadSafeQueue() = default;

/*
PRE: Recibe una referencia de un elemento de tipo T
(tipo de la elementos de la cola).
POST: Encola, por movimiento semantico, el elemento recibido
en la cola.
El elemento recibo queda en esta nulo.
*/
template <class T>
void ThreadSafeQueue<T>::push(T &element) {
    std::unique_lock<std::mutex> l(this->mutex);
    this->queue.push(std::move(element));
}

/*
PRE: Recibe una referencia a un elemento de tipo T
(tipo de la elementos de la cola).
POST: Desencola un elemento de cola y transfiere al 
elemento de referencia recibida los atributos del 
primero, devolviendo true; o false, si no se desencolo 
nada puesto que la cola esta vacia.
*/
template <class T>
bool ThreadSafeQueue<T>::pop(T &element) {
    std::unique_lock<std::mutex> l(this->mutex);
    if (this->queue.empty())
        return false;
    T task = std::move(queue.front());
    queue.pop();
    element = std::move(task);
    return true;
}

// Para usar este template, agregar aqui declaracion de clase
// Por ejemplo:
// template class ThreadSafaQueue<int>;