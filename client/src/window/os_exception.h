#ifndef OS_EXCEPTION_H
#define OS_EXCEPTION_H

#include <string>
#include <exception>

class OSException : public std::exception {
private:
    std::string description;
public:
    /*
    PRE: Recibe una descripcion propia (const char *) del error, y una descripcion
    del sistema operativo del mismo (const char *).
    POST: Inicializa una excepcion de OS.
    */
    OSException(const char* description, const char* oSError);
    
    /*Devuelve una descripcion (const char *) del error.*/
    const char* what() const noexcept;
};

#endif // OS_EXCEPTION_H
