//
// Created by franciscosicardi on 29/04/19.
//
#include <blocking_queue.h>

#include <protocol/event.h>
#include <protocol/object_moves_event.h>
#include <protocol/protocol_code.h>
#include <connector/connector.h>
#include <game_action.h>
#include <memory>

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
template class BlockingQueue<GameActionName>;
template class BlockingQueue<std::unique_ptr<GameAction>>;
template class BlockingQueue<std::unique_ptr<ObjectMovesEvent>>;

