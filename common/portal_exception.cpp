//
// Created by franciscosicardi on 12/05/19.
//

#include "portal_exception.h"

PortalException::PortalException(const std::string &msg):
                                 runtime_error("Portal exception: " + msg) {}

PortalException::~PortalException() = default;
