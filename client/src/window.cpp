#include "window.h"

#include "sdl_exception.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
PRE: Recibe:
    La longitud y altura del ventanta en pixeles (ambos int).
    La longitud de la ventana en la medida en que se ubican y 
    dimensionan los objetos del mapa representados en la 
    primera.
POST: Inicializa una ventana de las medidas recibidas.
Levanta SDLException en caso de error.
*/
Window::Window(int width, int height, int widthEquivalent)
: width(width), height(height), widthEquivalent(widthEquivalent) {
    int errCode = SDL_Init(SDL_INIT_VIDEO);
    if (errCode) {
        throw SdlException("Error en la inicialización", SDL_GetError());
    }
    errCode = SDL_CreateWindowAndRenderer(
        width, height, SDL_RENDERER_ACCELERATED,
        &this->window, &this->renderer);
    if (errCode) {
        throw SdlException("Error al crear ventana", SDL_GetError());
    }
}

/*Destruye la ventana.*/
Window::~Window() {
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }
    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
    SDL_Quit();
}

/*
PRE: Recibe un color descripto en coordenadas RGB 
(los tres int); y un valor de opacidad (int).
POST: Pinta la ventana del color recibido.
*/
void Window::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer,
                           r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

/*Pinta a la ventana de color gris*/
void Window::fill() {
    this->fill(0x33,0x33,0x33,0xFF);
}

/*
Renderiza todas las texturas que se agregaron a la ventana, 
en el orden en que fueron agregadas; y por la ultimo la ventana 
en si.
*/
void Window::render() {
    float adjuster = this->width/this->widthEquivalent;
    for (int i = 0; i < this->staticTextures.size(); ++i){
        this->staticTextures[i].render(adjuster);
    }
    SDL_RenderPresent(this->renderer);
}

/*
PRE: Recibe:
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
void Window::add_static_texture(const std::string & pathImage, 
                                Area areaSprite,
                                Area areaMap) {
    if (this->bigTextures.count(pathImage) == 0){
        BigTexture newBigTexture(this->renderer, pathImage);
        this->bigTextures.insert(mapStrBigTexture_t::value_type(
                                        pathImage, std::move(newBigTexture)));
    }
    StaticTexture newStaticTexture(this->bigTextures.at(pathImage), 
                                    std::move(areaSprite), std::move(areaMap));
    this->staticTextures.push_back(std::move(newStaticTexture));
}