//
// Created by franciscosicardi on 28/04/19.
//

#ifndef TP3_TALLER_SERVER_CLIENT_ACCEPTOR_H
#define TP3_TALLER_SERVER_CLIENT_ACCEPTOR_H


#include <string>
#include <thread>
#include "../common/socket.h"
#include "../common/blocking_queue.h"
#include "../common/connector.h"

class ClientAcceptor {
private:
    Socket acceptorSocket;
    BlockingQueue<Connector> &queue;
    std::thread thread;
    void execute();
public:
    ClientAcceptor(std::string &port, BlockingQueue<Connector> &queue);
    ~ClientAcceptor();
    void operator()();
    void join();
};


#endif //TP3_TALLER_SERVER_CLIENT_ACCEPTOR_H
