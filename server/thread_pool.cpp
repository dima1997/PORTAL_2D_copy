//
// Created by franciscosicardi on 09/05/19.
//

#include "thread_pool.h"

ThreadPool::ThreadPool(int n, BlockingQueue<Connector> &queue, GameManager &gameManager):
        executors() {
    for (int i = 0; i < n; i++) {
        auto executor = new RequestExecutor(queue, gameManager);
        executors.push_back(executor);
    }
}

ThreadPool::~ThreadPool() {
    for (auto executor : executors) {
        delete executor;
    }
}

void ThreadPool::start() {
    for (auto executor : executors) {
        (*executor)();
    }
}

void ThreadPool::stop() {
    for (auto executor : executors) {
        executor->join();
    }
}