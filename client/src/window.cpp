#include "window.h"

#include "sdl_exception.h"
#include "os_exception.h"
#include "images_paths.h"
#include "chell_texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <sstream>

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
    for (int i = 0; i < this->ids.size(); ++i){
        uint32_t actualId = this->ids[i];
        Renderizable & actualTexture = *(this->allTextures.at(actualId));
        actualTexture.render(adjuster);
    }
    SDL_RenderPresent(this->renderer);
}

/*
PRE: Recibe la ruta (const std::string &) de un gran textura 
(imagen con varios sprites en ella).
POST: Agrega la gran textura a la ventana, si que no se fue 
ya agregada.
Levanta SdlException en caso de error.
*/
void Window::add_big_texture(const std::string & pathImage){
    if (this->bigTextures.count(pathImage) == 0){
        BigTexture newBigTexture(this->renderer, pathImage);
        this->bigTextures.insert(mapStrBigTexture_t::value_type(
                                        pathImage, std::move(newBigTexture)));
    }
}

/*
PRE: Recibe:
    El id (const std::string &) de la textura a agregar.
    Una ruta (const std::string &) a una gran imagen que contiene el sprite
    de que utilizara la textura estatica a agregar.
    Un area (Area) con las coordenadas y dimensiones del sprite a usar de 
    la gran imagen (en pixeles).
    Un area (Area) con las coordenadas y dimensiones del objeto que 
    representa la textura en el mapa de juego (en unidades de distancia del 
    juego)
POST: Agrega un nueva textura estatica a la ventana, bajo las condiciones 
anteriores.
Levanta SdlException en caso de error.
*/
void Window::add_static_texture(uint32_t id, 
                                const std::string & pathImage, 
                                Area areaSprite,
                                Area areaMap) {
    if (this->allTextures.count(id) != 0){
        throw OSException("Error en ventana:","No puede haber dos texturas con el mismo id.");
    }
    this->add_big_texture(pathImage);
    this->ids.push_back(id); 
    std::unique_ptr<Renderizable> ptrTexture(
                                    new StaticTexture(
                                        this->bigTextures.at(pathImage), 
                                        std::move(areaSprite), 
                                        std::move(areaMap))
                                    );
    this->allTextures.insert(std::make_pair(id,std::move(ptrTexture)));
}

/*
PRE: Recibe :
    El id (uint32_t) de indentificacion de la chell a agregar.
    El area (Area) con las coordenadas y dimensiones del Chell del objeto
    que representa la textura en el mapa de juego (en unidades de distancia del 
    juego).
POST: Agrega un nueva textura de Chell a la ventana, bajo las condiciones anteriores.
Levanta OSException o SdlException en caso de error.
*/
void Window::add_chell_texture(uint32_t id, Area areaMap){
    if (this->allTextures.count(id) != 0){
        throw OSException("Error en ventana:","No puede haber dos texturas con el mismo id.");
    }
    this->add_big_texture(ALL_CHELL_SPRITES_PART_1);
    this->ids.push_back(id); 
    /*
    std::shared_ptr<Renderizable> ptrRenderTexture(
                                    new ChellTexture(
                                        this->bigTextures.at(
                                                ALL_CHELL_SPRITES_PART_1
                                            ), 
                                        std::move(areaMap))
                                    );
    */
    std::shared_ptr<Renderizable> ptrRenderTexture(
                                    new ChellTexture(
                                        this->bigTextures.at(
                                            ALL_CHELL_SPRITES_PART_1
                                        ), 
                                        std::move(areaMap)
                                    )
                                );
    std::shared_ptr<Movable> ptrMovableTexture;
    ptrMovableTexture = std::dynamic_pointer_cast<Movable>(ptrRenderTexture);
    this->allTextures.insert(std::make_pair(id,std::move(ptrRenderTexture)));
    this->movingTextures.insert(std::make_pair(
                                    id,std::move(ptrMovableTexture)
                                )
                        );
}

/*
PRE: Recibe un identificador de una textura movible, 
y nuevas coordenadas (float) x,y a donde desplazar la 
textura.
POST: Mueve la textura indicada en las coordenadas 
recibidas.
Levanta OSException en caso de error. 
*/
void Window::move_texture(uint32_t id, float x, float y){
    if (this->allTextures.count(id) == 0){
        std::stringstream errDescription; 
        errDescription << "No existe textura con id : " << std::dec << id << ".";
        throw OSException("Error en ventana:",errDescription.str().c_str());
    }
    Movable & idTexture = *(this->movingTextures.at(id));
    idTexture.move_to(x,y);
}