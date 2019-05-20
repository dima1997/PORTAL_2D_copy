#include "os_exception.h"

#include <string>

/*
PRE: Recibe una descripcion propia (const char *) del error, y una descripcion
del sistema operativo del mismo (const char *).
POST: Inicializa una excepcion de OS.
*/
OSException::OSException(const char* description, const char* oSError)
    : std::exception(), description(description) {
    this->description.append("\n OS_ERROR: ").append(oSError);
}

/*Devuelve una descripcion (const char *) del error.*/
const char* OSException::what() const noexcept{
    return this->description.c_str();
}
