//
// Created by franciscosicardi on 28/04/19.
//

#include <fstream>
#include <sstream>
#include <string>
#include "client_acceptor.h"

ClientAcceptor::ClientAcceptor(std::string &port, BlockingQueue<Connector> &queue):
               acceptorSocket(), queue(queue) {
    acceptorSocket.bind(port);
}

void ClientAcceptor::operator()() {
    thread = std::thread(&ClientAcceptor::execute, this);
}

void ClientAcceptor::join() {
    acceptorSocket.close();
    thread.join();
}

void ClientAcceptor::execute() {
    acceptorSocket.listen();
    while (true) {
        try {
            Connector connector(acceptorSocket.accept());
            queue.push(connector);
        } catch (const SocketException &e) {
            break;
        }
    }
}

ClientAcceptor::~ClientAcceptor() = default;
