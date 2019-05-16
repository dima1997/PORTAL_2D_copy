#ifndef WINDOW_H
#define WINDOW_H

#include "big_texture.h"
#include "static_texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector> 
#include <string>

typedef std::map<std::string, BigTexture> mapStrBigTexture_t;

class Window {
private:
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    mapStrBigTexture_t bigTextures;
    std::vector<StaticTexture> staticTextures;
public:
    /*
    PRE: Recibe una longitud y altura (ambos int).
    POST: Inicializa una ventana de las medidas recibidas.
    Levanta SDLException en caso de error.
    */
    Window(int width, int height);

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
    PRE: Recibe una ruta a una imagen de la cual crear un textura
    POST: Agrega un nueva textura statica en la posicion indicada.
    */

    void add_static_texture(const std::string & pathImage, 
                            unsigned int xImage, unsigned int yImage,
                            unsigned int width, unsigned int height,
                            unsigned int xPos, unsigned int yPos);
};

#endif // WINDOW_H