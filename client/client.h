//
// Created by franciscosicardi on 10/05/19.
//

#ifndef PORTAL_CLIENT_H
#define PORTAL_CLIENT_H


#include <string>
#include "../common/connector.h"

class Client {
private:
    Connector connector;
    std::string command;
public:
    Client(std::string &host, std::string &port, std::string &command);
    void operator()();
};


#endif //PORTAL_CLIENT_H
