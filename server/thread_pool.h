//
// Created by franciscosicardi on 09/05/19.
//

#ifndef PORTAL_THREADPOOL_H
#define PORTAL_THREADPOOL_H


#include "../common/blocking_queue.h"
#include "../common/connector.h"
#include "request_executor.h"
#include "game_manager.h"

class ThreadPool {
private:
    std::vector<RequestExecutor *> executors;
public:
    ThreadPool(int n, BlockingQueue<Connector> &queue, GameManager &gameManager);
    ~ThreadPool();
    void start();
    void stop();
};


#endif //PORTAL_THREADPOOL_H
