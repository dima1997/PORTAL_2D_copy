//
// Created by franciscosicardi on 18/04/19.
//

#ifndef TP3_TALLER_SOCKET_H
#define TP3_TALLER_SOCKET_H


#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include "socket_exception.h"

class Socket {
private:
    int fd;
    explicit Socket(int fd);
public:
    Socket();
    Socket(Socket &&socket) noexcept;
    ~Socket();
    void bind(const std::string &port);
    void listen();
    Socket accept();
    void connect(const std::string &host, const std::string &port);
    void shutDownRD();
    void shutDownWR();
    void close();
    void send(const void *data, size_t len);
    void receive(void *data, size_t len);
    Socket &operator=(const Socket &c) = delete;
    Socket &operator=(Socket &&c) noexcept;
};



#endif //TP3_TALLER_SOCKET_H
