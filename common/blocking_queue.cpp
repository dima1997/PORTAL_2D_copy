//
// Created by franciscosicardi on 29/04/19.
//

#include "blocking_queue.h"
#include "connector.h"
#include "protocol/event.h"

template <class T>
BlockingQueue<T>::BlockingQueue(): mutex(), cv(), queue() {}

template <class T>
BlockingQueue<T>::~BlockingQueue() = default;

template <class T>
void BlockingQueue<T>::push(T &element) {
    std::unique_lock<std::mutex> l(mutex);
    queue.push(std::move(element));
    cv.notify_one();
}

template <class T>
bool BlockingQueue<T>::pop(T &element) {
    std::unique_lock<std::mutex> l(mutex);
    cv.wait(l, [this]{ return !queue.empty() || closed; });
    if (queue.empty())
        return false;
    T task = std::move(queue.front());
    queue.pop();
    element = std::move(task);
    return true;
}

template <class T>
void BlockingQueue<T>::close() {
    std::unique_lock<std::mutex> l(mutex);
    closed = true;
    cv.notify_all();
}

// To use this template just add here, for example:
template class BlockingQueue<Connector>;
template class BlockingQueue<Event *>;