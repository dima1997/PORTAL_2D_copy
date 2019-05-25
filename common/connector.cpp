//
// Created by franciscosicardi on 09/05/19.
//

#include <cstdint>
#include "connector.h"

Connector::Connector() = default;

Connector::Connector(const std::string &host,
                     const std::string &port): socket() {
    socket.connect(host, port);
}

Connector::Connector(Socket socket): socket(std::move(socket)) {}

Connector::Connector(Connector &&other) noexcept {
    this->socket = std::move(other.socket);
}

Connector &Connector::operator=(Connector &&other) noexcept {
    this->socket = std::move(other.socket);
    return *this;
}

Connector &Connector::operator<<(const uint8_t &number) {
    socket.send(&number, sizeof(uint8_t));
    return *this;
}

Connector &Connector::operator>>(uint8_t &number) {
    socket.receive(&number, sizeof(uint8_t));
    return *this;
}

Connector::~Connector() = default;
