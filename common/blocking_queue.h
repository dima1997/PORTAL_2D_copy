#ifndef TP3_TALLER_BLOCKING_QUEUE_H
#define TP3_TALLER_BLOCKING_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class BlockingQueue {
private:
    std::mutex mutex;
    std::condition_variable cv;
    std::queue<T> queue;
    bool closed = false;
public:    
    BlockingQueue() 
    :   mutex(), cv(), queue() {}
    
    ~BlockingQueue() = default;

    void push(T &element) {
        std::unique_lock<std::mutex> l(mutex);
        queue.push(std::move(element));
        cv.notify_one();
    }

    bool pop(T &element) {
        std::unique_lock<std::mutex> l(mutex);
        cv.wait(l, [this]{ return !queue.empty() || closed; });
        if (queue.empty())
            return false;
        element = std::move(queue.front());
        queue.pop();
        return true;
    }

    void close() {
        std::unique_lock<std::mutex> l(mutex);
        closed = true;
        cv.notify_all();
    }

    BlockingQueue(BlockingQueue<T> &&other) noexcept
    :   mutex(), 
        cv(), 
        queue(std::move(other.queue)), 
        closed(other.closed) {}
};

#endif //TP3_TALLER_BLOCKING_QUEUE_H
