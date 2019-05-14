//
// Created by franciscosicardi on 09/05/19.
//

#ifndef PORTAL_CONNECTOR_H
#define PORTAL_CONNECTOR_H


#include "socket.h"

class Connector {
private:
    Socket socket;
public:
    Connector();
    Connector(Connector &&other) noexcept;
    Connector(const std::string &host, const std::string &port);
    explicit Connector(Socket socket);
    ~Connector();
    Connector &operator=(Connector &&other) noexcept;
    Connector &operator<<(const uint8_t &number);
    Connector &operator>>(uint8_t &number);
};


#endif //PORTAL_CONNECTOR_H
