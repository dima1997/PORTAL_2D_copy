//
// Created by franciscosicardi on 10/05/19.
//

#ifndef PORTAL_CLIENT_H
#define PORTAL_CLIENT_H

#include <string>

class Client {
public:
    Client();
    void operator()(std::string &host, std::string &port, std::string &command, uint8_t id);
    void run();
};


#endif //PORTAL_CLIENT_H
