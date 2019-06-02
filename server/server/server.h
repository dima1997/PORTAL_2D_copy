//
// Created by franciscosicardi on 09/05/19.
//

#ifndef PORTAL_SERVER_H
#define PORTAL_SERVER_H


#include <blocking_queue.h>
#include <connector/connector.h>
#include "thread_pool.h"
#include "client_acceptor.h"
#include "../game/game_manager.h"

class Server {
private:
    BlockingQueue<Connector> queue;
    ClientAcceptor clientAcceptor;
    GameManager gameManager;
    ThreadPool threadPool;
public:
    explicit Server(std::string &port);
    void operator()();
};


#endif //PORTAL_SERVER_H
