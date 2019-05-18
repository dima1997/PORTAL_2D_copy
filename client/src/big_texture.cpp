#include "big_texture.h"

#include "sdl_exception.h"
#include "area.h"

#include <SDL2/SDL_image.h>

/*
PRE: Recibe la ruta (const std::string &) de un archivo con un textura.
POST: Devuelve una textura (SDL_Texture *) con la textura cargada.
Levanta SDLException en caso de error. 
*/
SDL_Texture* BigTexture::loadTexture(const std::string & pathImage) {
    SDL_Texture* texture = IMG_LoadTexture(this->renderer,
                                           pathImage.c_str());
    if (!texture) {
        throw SdlException("Error al cargar la textura.", SDL_GetError());
    }
    return texture;
}

/*
PRE: Recibe un puntero al renderizador (SDL_Renderer *) de la ventana donde 
la textura se muestra; y la ruta a la imagen que utilizara la textura.
POST: Inicializa una textura de la imagen de la ruta recibida.
Levanta SdlExceptionE en caso de error.
*/
BigTexture::BigTexture(SDL_Renderer* renderer, const std::string & pathImage) {
    this->renderer = renderer;
    this->texture = this->loadTexture(pathImage);
}

/*Destruye la gran textura*/
BigTexture::~BigTexture(){
    SDL_DestroyTexture(this->texture);
}

/*
PRE: Recibe una doble referenia a otra gran textura (BigTexture &&).
POST: Construye una nueva gran textura por movimiento semantico.
La gran textura recibida queda en estado nulo.
*/
BigTexture::BigTexture(BigTexture && otherBigTexture) {
    this->renderer = otherBigTexture.renderer;
    this->texture = otherBigTexture.texture;
    otherBigTexture.renderer = NULL;
    otherBigTexture.texture = NULL;
}

/*
PRE: Recibe una doble referenia a otra gran textura (BigTexture &&).
POST: Asigna por movimiento semantico. Devuelve una referencia a 
la gran textura actual.
La gran textura recibida queda en estado nulo.
*/
BigTexture & BigTexture::operator=(BigTexture && otherBigTexture) {
    if (this == &otherBigTexture){
        return *this;
    }
    this->renderer = otherBigTexture.renderer;
    this->texture = otherBigTexture.texture;
    otherBigTexture.renderer = NULL;
    otherBigTexture.texture = NULL;
    return *this;
}   

/*
PRE: Recibe dos areas (Area &):
        La primera correspondiente al pedazo de textura actual 
        que se desea mostrar.
        La segunda corresponde al lugar y espacio (de la ventana) 
        donde se va a ajustar la imagen definida por la primer area.
    Tambien recibe un flip a realizar sobre el sprite a renderizar 
    (textureFlip_t)
POST: Renderiza la textura bajo las condiciones anteriores.
Levanta SdlException en caso de error.
*/
void BigTexture::render(const Area & src, const Area & dest, textureFlip_t flip){
    SDL_Rect sdlSrc = {
            (int)src.getX(), (int)src.getY(),
            (int)src.getWidth(), (int)src.getHeight()
    };
    SDL_Rect sdlDest = {
            (int)dest.getX(), (int)dest.getY(),
            (int)dest.getWidth(), (int)dest.getHeight()
    };
    SDL_RendererFlip sdlFlip = SDL_FLIP_NONE;
    if (flip == FLIP_HORIZONTAL) {
        sdlFlip = SDL_FLIP_HORIZONTAL;
    }
    //return SDL_RenderCopy(this->renderer, this->texture, & sdlSrc, & sdlDest);
    int sdlError = SDL_RenderCopyEx(this->renderer,this->texture, 
                                    & sdlSrc, & sdlDest, 
                                    0, NULL, sdlFlip);
    if (sdlError != 0){
        throw SdlException("Error al renderizar gran textura.",SDL_GetError());
    }
}

