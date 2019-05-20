#include "sdl_exception.h"

#include <SDL2/SDL_image.h>

#include <string>

/*
PRE: Recibe una descripcion propia (const char *) del error, y una descripcion
del sistema operativo del mismo (const char *).
POST: Inicializa una excepcion de SDL.
*/
SdlException::SdlException(const char* description, const char* sdlError)
    : std::exception(), description(description) {
    this->description.append("\n SDL_ERROR: ").append(sdlError);
}

/*Devuelve una descripcion (const char *) de la excepcion SDL*/
const char* SdlException::what() const noexcept{
    return this->description.c_str();
}
