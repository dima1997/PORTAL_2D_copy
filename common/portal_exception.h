//
// Created by franciscosicardi on 12/05/19.
//

#ifndef PORTAL_PORTAL_EXCEPTION_H
#define PORTAL_PORTAL_EXCEPTION_H


#include <stdexcept>

class PortalException: public std::runtime_error {
public:
    explicit PortalException(const std::string &msg);
    ~PortalException() override;
};


#endif //PORTAL_PORTAL_EXCEPTION_H
