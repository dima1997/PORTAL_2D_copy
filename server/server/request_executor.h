//
// Created by franciscosicardi on 09/05/19.
//

#ifndef PORTAL_REQUEST_EXECUTOR_H
#define PORTAL_REQUEST_EXECUTOR_H

#include <thread>
#include "blocking_queue.h"
#include "connector/connector.h"
#include "../game/game_manager.h"

class RequestExecutor {
private:
    BlockingQueue<Connector> &queue;
    std::thread thread;
    void execute();
    GameManager &gameManager;
public:
    RequestExecutor(BlockingQueue<Connector> &queue, GameManager &gameManager);
    ~RequestExecutor();
    void operator()();
    void join();
};


#endif //PORTAL_REQUEST_EXECUTOR_H
