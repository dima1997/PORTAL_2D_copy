#include "../../includes/window/window.h"

#include "../../includes/window/os_exception.h"
#include "../../includes/window/texture_factory.h"
#include "../../includes/window/map_creator.h"
#include "../../includes/textures/common_texture/big_texture.h"
#include "../../includes/textures/common_texture/texture.h"
#include "../../includes/textures/common_texture/sdl_exception.h"

#include "../../includes/mixer/mixer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include <mutex>

/*
PRE: Recibe la ruta (const std::string &) de un gran textura 
(imagen con varios sprites en ella).
POST: Agrega la gran textura a la ventana, si que no se fue 
ya agregada.
Levanta SdlException en caso de error.
*/
BigTexture & Window::add_big_texture(const std::string & pathImage){
    if (this->bigTextures.count(pathImage) == 0){
        BigTexture newBigTexture(this->renderer, pathImage);
        this->bigTextures.insert(std::map<std::string, BigTexture>::value_type(
                                        pathImage, std::move(newBigTexture)));
    }
    return this->bigTextures.at(pathImage);
}

/*
PRE: Recibe el id de la textura a agregar.
POST: Agrega la textura al la ventana.
Levanta OSError si el id recibdo ya fue previamente agregado.
*/
void Window::add_id_texture(uint32_t id){
    if (this->allTextures.count(id) != 0){
        std::stringstream errMsj;
        errMsj << "No puede haber dos texturas con el mismo id: " << id << ".";
        throw OSException("Error en ventana:",errMsj.str().c_str());
    }
    this->ids.push_back(id);
}

/*
PRE: Recibe el id (uint32_t) de la textura a agregar, y un puntero
unico a textura (std::unique_ptr<Texture>) de la textura a agregar.
POST: Agrega la textura recibida.
*/
void Window::add_texture(uint32_t id, std::unique_ptr<Texture> ptrTexture) {
    this->add_id_texture(id);
    this->allTextures.insert(std::make_pair(id,std::move(ptrTexture)));
}

/*
PRE: Recibe:
    La longitud y altura del ventanta en pixeles (ambos int).
    El id de la textura en la que se centrara e indicarara que mostrar 
    en la ventana.
    La configuracion del mapa de juego (YAML::Node &).
POST: Inicializa una ventana de las medidas recibidas.
Levanta SDLException en caso de error.
*/
Window::Window(int width, int height, uint32_t idMainTexture, 
               YAML::Node & mapConfig)
: width(width), height(height), idMainTexture(idMainTexture) {
    this->window = SDL_CreateWindow(
        "Portal Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_RESIZABLE);
    if (this->window == NULL){
        throw SdlException("Error al crear ventana.", SDL_GetError());
    }
    this->renderer = SDL_CreateRenderer(this->window,-1,SDL_RENDERER_ACCELERATED);
    if (this->renderer == NULL) {
        SDL_DestroyWindow(this->window);
        throw SdlException("Error al crear renderizador.", SDL_GetError());   
    }
    MapCreator mapCreator(mapConfig,*this);
    mapCreator.add_map(); 
    {
        std::unique_lock<std::mutex> l(this->mutex);
        Texture & mainTexture = *(this->allTextures.at(this->idMainTexture));
        this->areaCamera = mainTexture.getVisionArea(); 
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
    this->fill();
    Texture & mainTexture = *(this->allTextures.at(this->idMainTexture));
    Area newAreaCamera = mainTexture.getVisionArea(); 
    int widthPixels;
    int heightPixels;
    SDL_GetWindowSize(this->window,&widthPixels,&heightPixels);
    float adjuster;
    if (widthPixels <= heightPixels){
        adjuster = widthPixels/newAreaCamera.getWidth();
        float newHeight = heightPixels/adjuster;
        newAreaCamera.setHeight(newHeight);
    } else {
        adjuster = heightPixels/newAreaCamera.getHeight();
        float newWidth = widthPixels/adjuster;
        newAreaCamera.setWidth(newWidth);
    }
    for (int i = 0; i < (int)this->ids.size(); ++i){
        uint32_t actualId = this->ids[i];
        Texture & actualTexture = *(this->allTextures.at(actualId));
        actualTexture.render(adjuster, newAreaCamera);
    }
    SDL_RenderPresent(this->renderer);
    {
        std::unique_lock<std::mutex> l(this->mutex);
        this->areaCamera = newAreaCamera;
    }
}

/*
PRE: Recibe un identificador (uint32_t) de una textura, 
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
    Texture & textureOfId = *(this->allTextures.at(id));
    textureOfId.move_to(x,y);
}

/*
PRE: Recibe un identificador (uint32_t) de una textura.
POST: Switchea el sprite de la textura.
Levanta OSException en caso de error. 
*/
void Window::switch_texture(uint32_t id){
    if (this->allTextures.count(id) == 0){
        std::stringstream errDescription; 
        errDescription << "No existe textura con id : " << std::dec << id << ".";
        throw OSException("Error en ventana:",errDescription.str().c_str());
    }
    Texture & textureOfId = *(this->allTextures.at(id));
    textureOfId.switch_sprite();
}

/*
Devuelve una referencia constante al area (const Area &) 
de la textura de Chell principal de la ventana.
*/
const Area Window::getMainTextureArea() {
    return (*(this->allTextures.at(this->idMainTexture))).getAreaMap();
}

/*
PRE: Recibe las coordenadas x,y (int) en pixeles 
de algun punto en la ventana.
POST: Devuelve las coordenadas x,y (float) de dicho 
punto en el mapa de juego. 
*/
std::tuple<float,float> Window::getMapCoords(int x, int y){
    Area actualAreaCamera;
    int actualWidth;
    int actualHeight;
    {
        std::unique_lock<std::mutex> l(this->mutex);
        actualAreaCamera = this->areaCamera;
        SDL_GetWindowSize(this->window, &actualWidth, &actualHeight);
    }
    Area areaCameraTopLeft = actualAreaCamera.from_center_to_top_left();
    float reverseAdjuster = (areaCameraTopLeft.getWidth()/actualWidth);
    float xMap = x * reverseAdjuster;
    float yMap = y * reverseAdjuster;
    xMap = xMap + areaCameraTopLeft.getX();
    yMap = (-yMap + areaCameraTopLeft.getY());
    return std::move(std::tuple<float,float>(xMap,yMap));
}

/*
Reproduce los sonidos de todas 
las textura de la ventana.
*/
void Window::sound(Mixer & mixer){
    for (int i = 0; i < (int)this->ids.size(); ++i){
        uint32_t actualId = this->ids[i];
        Texture & actualTexture = *(this->allTextures.at(actualId));
        actualTexture.sound(mixer);
    }
}