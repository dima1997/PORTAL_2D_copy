#include "thread_safe_queue.h"

#include <protocol/protocol_code.h>

#include <memory>
#include <protocol/game_action/game_action.h>

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

template<class T>
ThreadSafeQueue<T>::ThreadSafeQueue(ThreadSafeQueue<T> &&other) noexcept:
                                    mutex(), queue(std::move(other.queue)) {}

template<class T>
ThreadSafeQueue<T> &ThreadSafeQueue<T>::operator=(ThreadSafeQueue<T> &&other) noexcept {
    this->queue = std::move(other.queue);
    return *this;
}

// To use this template just add here, for example:
//template class ThreadSafaQueue<int>;
template class ThreadSafeQueue<std::unique_ptr<ObjectMovesEvent>>;
template class ThreadSafeQueue<std::pair<uint32_t, gameObjectAction_t>>;
//template class ThreadSafeQueue<GameAction *>;
template class ThreadSafeQueue<std::unique_ptr<Event>>;
template class ThreadSafeQueue<std::unique_ptr<GameAction>>;
template class ThreadSafeQueue<GameActionName>;

