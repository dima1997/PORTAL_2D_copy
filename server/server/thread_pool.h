//
// Created by franciscosicardi on 09/05/19.
//

#ifndef PORTAL_THREADPOOL_H
#define PORTAL_THREADPOOL_H


#include <blocking_queue.h>
#include <connector/connector.h>
#include "request_executor.h"
#include "../game/game_manager.h"

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
