#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <queue>
#include <mutex>

template <class T>
class ThreadSafeQueue {
private:
    std::mutex mutex;
    std::queue<T> queue;

public:
    /*
    Inicializa una cola segura en hilos de ejecucion,
    no bloqueante, de elemento tipo T.
    T debe implementar constructor y asignacion por 
    movimiento semantico.
    */
    ThreadSafeQueue(): mutex(), queue() {}

    /*
    Destruye un la cola segura en hilos de ejecucion,
    no bloqueante. 
    */
    ~ThreadSafeQueue() = default;

    /*
    PRE: Recibe una referencia de un elemento de tipo T
    (tipo de la elementos de la cola).
    POST: Encola, por movimiento semantico, el elemento recibido
    en la cola.
    El elemento recibo queda en esta nulo.
    */
    void push(T &element) {
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
    bool pop(T &element) {
        std::unique_lock<std::mutex> l(this->mutex);
        if (this->queue.empty())
            return false;
        T task = std::move(queue.front());
        queue.pop();
        element = std::move(task);
        return true;
    }

    ThreadSafeQueue(ThreadSafeQueue<T> &&other) noexcept:
                                    mutex(), queue(std::move(other.queue)) {}

    ThreadSafeQueue<T> &operator=(ThreadSafeQueue<T> &&other) noexcept {
        this->queue = std::move(other.queue);
        return *this;
    }
};

#endif // THREAD_SAFE_QUEUE_H
