#include "../../includes/user_interface/message_exception.h"

#include <string>
#include <stdexcept>

/*
PRE: Recibe un mensaje de error (const std::string &).
POST: Inicializa un mensaje de error.
*/
MessageException::MessageException(const std::string & msg)
:   runtime_error(msg) {}

MessageException::~MessageException() = default;
