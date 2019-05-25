//
// Created by franciscosicardi on 19/04/19.
//

#ifndef TP3_TALLER_SOCKET_EXCEPTION_H
#define TP3_TALLER_SOCKET_EXCEPTION_H

#include <string>
#include <stdexcept>


class SocketException: public std::runtime_error {
public:
    explicit SocketException(const std::string &msg) noexcept;
    ~SocketException() override;
};


#endif //TP3_TALLER_SOCKET_EXCEPTION_H
