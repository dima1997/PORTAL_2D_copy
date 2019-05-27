#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <queue>
#include <mutex>

#include <memory>
#include <protocol/event/object_moves_event.h>

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
    ThreadSafeQueue();

    ThreadSafeQueue(ThreadSafeQueue<T> &&other) noexcept;

    ThreadSafeQueue<T> &operator=(ThreadSafeQueue<T> &&other) noexcept;

    /*
    Destruye un la cola segura en hilos de ejecucion,
    no bloqueante. 
    */
    ~ThreadSafeQueue();

    /*
    PRE: Recibe una referencia de un elemento de tipo T
    (tipo de la elementos de la cola).
    POST: Encola, por movimiento semantico, el elemento recibido
    en la cola.
    El elemento recibo queda en esta nulo.
    */
    void push(T &element);

    /*
    PRE: Recibe una referencia a un elemento de tipo T
    (tipo de la elementos de la cola).
    POST: Desencola un elemento de cola y transfiere al 
    elemento de referencia recibida los atributos del 
    primero, devolviendo true; o false, si no se desencolo 
    nada puesto que la cola esta vacia.
    */
    bool pop(T &element);
};

enum gameObjectAction_t : uint32_t {
    MOVE_LEFT,
    MOVE_RIGHT
};

typedef ThreadSafeQueue<std::unique_ptr<ObjectMovesEvent>>
TSQueueChangesMade_t;

typedef ThreadSafeQueue<std::pair<uint32_t, gameObjectAction_t>> 
TSQueueChangesAsk_t;

#endif // THREAD_SAFE_QUEUE_H