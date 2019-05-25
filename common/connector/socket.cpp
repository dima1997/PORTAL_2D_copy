//
// Created by franciscosicardi on 18/04/19.
//

#define _POSIX_C_SOURCE 200112L

#include <netdb.h>
#include <unistd.h>
#include <string>
#include "socket.h"

#define MAX_QUEUE 20

Socket::Socket(int fd): fd(fd) {}

Socket::Socket() {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) throw SocketException("Couldn't create socket.");
}

Socket::~Socket() {
    if (fd > 0) {
        this->close();
    }
}

void Socket::bind(const std::string &port) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    struct addrinfo *ai_list;
    getaddrinfo(nullptr, port.c_str(), &hints, &ai_list);
    struct addrinfo *ptr;
    bool bound = false;
    for (ptr = ai_list;
         ptr != nullptr && !bound;
         ptr = ptr->ai_next) {
        if (::bind(fd, ai_list->ai_addr, ai_list->ai_addrlen) == 0) {
            bound = true;
        }
    }
    freeaddrinfo(ai_list);
    if (!bound) throw SocketException(strerror(errno));
}

void Socket::listen() {
    if (::listen(fd, MAX_QUEUE) == -1) throw SocketException(strerror(errno));
}

Socket Socket::accept() {
    int socket_fd = ::accept(fd, nullptr, nullptr);
    if (socket_fd == -1) throw SocketException(strerror(errno));
    return Socket(socket_fd);
}

void Socket::connect(const std::string &host, const std::string &port) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    struct addrinfo *ai_list;
    int gai = getaddrinfo(host.c_str(), port.c_str(), &hints, &ai_list);
    if (gai != 0) {
        throw SocketException(gai_strerror(gai));
    }
    struct addrinfo *ptr;
    bool conn = false;
    for (ptr = ai_list; ptr != nullptr && !conn; ptr = ptr->ai_next) {
        int s = ::connect(fd, ptr->ai_addr, ptr->ai_addrlen);
        conn = (s != -1);
    }
    freeaddrinfo(ai_list);
    if (!conn) throw SocketException(strerror(errno));
}

void Socket::shutDownRD() {
    shutdown(fd, SHUT_RD);
}

void Socket::shutDownWR() {
    shutdown(fd, SHUT_WR);
}

void Socket::send(const void *data, size_t len) {
    size_t sent = 0;
    ssize_t s = 0;
    while (sent < len) {
        s = ::send(fd, (char *)data + sent,
                   len - sent, MSG_NOSIGNAL);
        if (s >= 0) {
            sent += s;
        } else {
            throw SocketException(strerror(errno));
        }
    }
    if (sent != len) throw SocketException("Couldn't send all data.");
}

void Socket::receive(void *data, size_t len) {
    size_t received = 0;
    do {
        ssize_t s = ::recv(fd, (char *)data + received, len * sizeof(char), 0);
        if (s > 0) {
            received += s;
        } else if (s == 0) {
            throw SocketException("Connection was closed by peer.");
        } else {
            throw SocketException(strerror(errno));
        }
    } while (received < len);
}

Socket::Socket(Socket &&socket) noexcept {
    this->fd = socket.fd;
    socket.fd = -1;
}

Socket &Socket::operator=(Socket &&other) noexcept {
    if (this == &other) return *this;
    this->fd = other.fd;
    other.fd = -1;
    return *this;
}

void Socket::close() {
    shutdown(fd, SHUT_RDWR);
    ::close(fd);
}
