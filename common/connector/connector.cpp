//
// Created by franciscosicardi on 09/05/19.
//

#include <cstdint>
#include <sstream>
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

Connector &Connector::operator<<(const std::string &string) {
    auto str_len = htobe32((uint32_t)string.size());
    socket.send(&str_len, sizeof(uint32_t));
    const char *str = string.c_str();
    socket.send(str, string.size());
    return *this;
}

Connector &Connector::operator>>(std::string &string) {
    uint32_t _str_len;
    socket.receive(&_str_len, sizeof(uint32_t));
    uint32_t str_len = be32toh(_str_len);
    char *str = new char[str_len + 1];
    socket.receive(str, str_len);
    str[str_len] = '\0';
    string.assign(str);
    delete[] str;
    return *this;
}

Connector &Connector::operator<<(const uint16_t &_number) {
    uint16_t number = htobe16(_number);
    socket.send(&number, sizeof(uint16_t));
    return *this;
}

Connector &Connector::operator>>(uint16_t &number) {
    uint16_t _number;
    socket.receive(&_number, sizeof(uint16_t));
    number = be16toh(_number);
    return *this;
}

Connector &Connector::operator<<(const uint32_t &_number) {
    uint32_t number = htobe32(_number);
    socket.send(&number, sizeof(uint32_t));
    return *this;
}

Connector &Connector::operator>>(uint32_t &number) {
    uint32_t _number;
    socket.receive(&_number, sizeof(uint32_t));
    number = be16toh(_number);
    return *this;
}

Connector &Connector::operator<<(const float &number) {
    std::ostringstream ss;
    ss << number;
    std::string s(ss.str());
    return *this << s;
}

Connector &Connector::operator>>(float &number) {
    std::string s;
    *this >> s;
    number = ::strtod(s.c_str(), nullptr);
    return *this;
}

Connector::~Connector() = default;

/*Cierra la conexion de lectura.*/
void Connector::shutDownRD() {
    this->socket.shutDownRD();
}

/*Cierra la conexion de escritura.*/
void Connector::shutDownWR() {
    this->socket.shutDownWR();
}
