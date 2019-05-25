#ifndef BIG_TEXTURA_H
#define BIG_TEXTURA_H

#include "area.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

enum textureFlip_t {
    NO_FLIP,
    FLIP_HORIZONTAL
};

class BigTexture {
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    /*
    PRE: Recibe la ruta (const std::string &) de un archivo con un textura.
    POST: Devuelve una textura (SDL_Texture *) con la textura cargada.
    Levanta SDLException en caso de error. 
    */
    SDL_Texture * loadTexture(const std::string & pathImage);
public:
    /*
    PRE: Recibe un puntero al renderizador (SDL_Renderer *) de la ventana donde 
    la textura se muestra; y la ruta a la imagen que utilizara la textura.
    POST: Inicializa una textura de la imagen de la ruta recibida.
    Levanta SdlException en caso de error.
    */
    BigTexture(SDL_Renderer * renderer, const std::string & pathImage);

    /*Destruye la gran textura*/
    ~BigTexture();

    //Move semantics

    /*
    PRE: Recibe una doble referenia a otra gran textura (BigTexture &&).
    POST: Construye una nueva gran textura por movimiento semantico.
    La gran textura recibida queda en estado nulo.
    */
    BigTexture(BigTexture && otherBigTexture);
    
    /*
    PRE: Recibe una doble referenia a otra gran textura (BigTexture &&).
    POST: Asigna por movimiento semantico. Devuelve una referencia a 
    la gran textura actual.
    La gran textura recibida queda en estado nulo.
    */
    BigTexture & operator=(BigTexture && otherBigTexture);

    // No permite copias implicitas
    BigTexture(const BigTexture & otherBigTexture) = delete;
    BigTexture & operator=(const BigTexture & otherBigTexture) = delete;    

    /*
    PRE: Recibe dos areas (Area &):
            La primera corresponde al pedazo de textura actual 
            que se desea mostrar.
            La segunda corresponde al lugar y espacio (de la ventana) 
            deonde se va a ajustar la imagen definida por la primer area.
        Tambien recibe un flip a realizar sobre el sprite a renderizar 
        (textureFlip_t)
    POST: Renderiza la textura bajo las condiciones anteriores.
    Levanta SdlException en caso de error.
    */
    void render(const Area & src, const Area & dest, textureFlip_t flip); 
};

#endif // BIG_TEXTURA_H