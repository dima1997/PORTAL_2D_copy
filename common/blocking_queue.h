//
// Created by franciscosicardi on 29/04/19.
//

#ifndef TP3_TALLER_BLOCKING_QUEUE_H
#define TP3_TALLER_BLOCKING_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

#include <cstdint>
#include "../client/src/common_texture/texture_move_change.h"
#include <memory>

template <class T>
class BlockingQueue {
private:
    std::mutex mutex;
    std::condition_variable cv;
    std::queue<T> queue;
    bool closed = false;
public:
    BlockingQueue();
    ~BlockingQueue();
    void push(T &element);
    bool pop(T &element);
    void close();
};

#endif //TP3_TALLER_BLOCKING_QUEUE_H
