#ifndef WINDOW_H
#define WINDOW_H

#include "big_texture.h"
#include "static_texture.h"
#include "renderizable.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector> 
#include <string>
#include <cstdint>
#include <memory>

typedef std::map<std::string, BigTexture> mapStrBigTexture_t;

class Window {
private:
    int width;
    int height;
    int widthEquivalent;
    SDL_Window* window;
    SDL_Renderer* renderer;
    mapStrBigTexture_t bigTextures;
    std::vector<uint32_t> ids;
    std::map<uint32_t, std::unique_ptr<Renderizable>> renderizables;
public:
    /*
    PRE: Recibe:
        La longitud y altura del ventanta en pixeles (ambos int).
        La longitud de la ventana equivalente en la medida en que
        se ubican y dimensionan los objetos son representados en la 
        misma.
    POST: Inicializa una ventana de las medidas recibidas.
    Levanta SDLException en caso de error.
    */
    Window(int width, int height, int widthEquivalent);

    /*Destruye la ventana.*/
    ~Window();

    /*
    PRE: Recibe un color descripto en coordenadas RGB 
    (los tres int); y un valor de opacidad (int).
    POST: Pinta la ventana del color recibido.
    */
    void fill(int r, int g, int b, int alpha);

    /*Pinta a la ventana de color gris*/
    void fill();

    /*
    Renderiza todas las texturas que se agregaron a la ventana, 
    en el orden en que fueron agregadas; y por la ultimo la ventana 
    en si.
    */
    void render();

    /*
    PRE: Recibe la ruta (const std::string &) de un gran textura 
    (imagen con varios sprites en ella).
    POST: Agrega la gran textura a la ventana, si que no se fue 
    ya agregada.
    Levanta SdlException en caso de error.
    */
    void add_big_texture(const std::string & pathImage);

    /*
    PRE: Recibe:
        El id (uint32_t) de la textura a agregar.
        Una ruta (const std::string &) a una gran imagen que contiene el sprite
        de que utilizara la textura estatica a agregar.
        Un area (Area) con las coordenadas y dimensiones del sprite a usar de 
        la gran imagen (en pixeles).
        Un area (Area) con las coordenadas y dimensiones del objeto que 
        representa la textura en el mapa de juego (en la unidad del largo 
        equivalente de la ventanta).
    POST: Agrega un nueva textura estatica a la ventana, bajo las condiciones 
    anteriores.
    */
    void add_static_texture(uint32_t id, 
                            const std::string & pathImage, 
                            Area areaSprite,
                            Area areaMap);

    /*
    PRE: Recibe :
        El id (uint32_t) de indentificacion de la chell a agregar.
        El area (Area) con las coordenadas y dimensiones del Chell del objeto
        que representa la textura en el mapa de juego (en unidades de distancia del 
        juego).
    POST: Agrega un nueva textura de Chell a la ventana, bajo las condiciones anteriores.
    Levanta SdlException en caso de error.
    */
    void add_chell_texture(uint32_t id, Area areaMap);

};

#endif // WINDOW_H