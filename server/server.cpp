//
// Created by franciscosicardi on 09/05/19.
//

#include <iostream>
#include "server.h"

#define NUMBER_OF_THREADS 10

Server::Server(std::string &port): queue(), clientAcceptor(port, queue),
                                   gameManager(),
                                   threadPool(NUMBER_OF_THREADS, queue, gameManager) {}

void Server::operator()() {
    clientAcceptor();
    threadPool.start();
    while (int c = std::cin.get()) {
        if ((char)c == 'q') break;
    }
    queue.close();
    clientAcceptor.join();
    threadPool.stop();
}
