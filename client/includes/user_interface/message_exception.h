#ifndef MESSAGE_EXCEPTION_H
#define MESSAGE_EXCEPTION_H

#include <stdexcept>

class MessageException : public std::runtime_error {
public:
    explicit MessageException(const std::string & msg);
    virtual ~MessageException() override;
};

#endif //MESSAGE_EXCEPTION_H
