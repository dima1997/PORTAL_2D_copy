#ifndef __SDL_EXCEPTION_H__
#define __SDL_EXCEPTION_H__
#include <string>
#include <exception>

class SdlException : public std::exception {
private:
    std::string description;
public:
    /*
    PRE: Recibe una descripcion propia (const char *) del error, y una descripcion
    del sistema operativo del mismo (const char *).
    POST: Inicializa una excepcion de SDL.
    */
    SdlException(const char* description, const char* sdlError);

    /*Devuelve una descripcion (const char *) de la excepcion SDL*/
    const char* what() const noexcept;
};

#endif
