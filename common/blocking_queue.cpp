//
// Created by franciscosicardi on 29/04/19.
//
#include <blocking_queue.h>

#include <protocol/event/event.h>
#include <protocol/event/object_moves_event.h>
#include <connector/connector.h>
#include "blocking_queue.h"
#include "protocol/game_action/game_action.h"
#include <protocol/protocol_code.h>
#include <connector/connector.h>
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
    element = std::move(queue.front());
    queue.pop();
//    element = std::move(task);
    return true;
}

template <class T>
void BlockingQueue<T>::close() {
    std::unique_lock<std::mutex> l(mutex);
    closed = true;
    cv.notify_all();
}

template<class T>
BlockingQueue<T>::BlockingQueue(BlockingQueue<T> &&other) noexcept:
                                mutex(), cv(), queue(std::move(other.queue)), closed(other.closed) {}

// To use this template just add here, for example:
template class BlockingQueue<Connector>;
template class BlockingQueue<std::shared_ptr<Event>>;
template class BlockingQueue<GameActionName>;
template class BlockingQueue<std::unique_ptr<GameAction>>;
template class BlockingQueue<std::unique_ptr<ObjectMovesEvent>>;
template class BlockingQueue<std::vector<char>>;

