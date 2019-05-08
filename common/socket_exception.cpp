#include <utility>

//
// Created by franciscosicardi on 19/04/19.
//

#include <string>
#include "socket_exception.h"

SocketException::SocketException(const std::string &msg) noexcept:
                    runtime_error("Socket exception: " + msg + "\n") {}

SocketException::~SocketException() = default;
