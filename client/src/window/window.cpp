#include "../../includes/window/window.h"

#include "../../includes/window/os_exception.h"
#include "../../includes/textures/common_texture/big_texture.h"
#include "../../includes/textures/common_texture/texture.h"
#include "../../includes/textures/common_texture/sdl_exception.h"
#include "../../includes/textures/common_texture/images_paths.h"

#include "../../includes/textures/chell_texture/chell_texture.h"
#include "../../includes/textures/block_metal_texture/block_metal_texture.h"

#include "../../includes/game_objects/game_objects_size.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <sstream>

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
        this->bigTextures.insert(std::map<std::string, BigTexture>::value_type(
                                        pathImage, std::move(newBigTexture)));
    }
}

/*
PRE: Recibe el id de la textura a agregar.
POST: Agrega la textura al la ventana.
Levanta OSError si el id recibdo ya fue previamente agregado.
*/
void Window::add_id_texture(uint32_t id){
    if (this->allTextures.count(id) != 0){
        throw OSException("Error en ventana:","No puede haber dos texturas con el mismo id.");
    }
    this->ids.push_back(id);
}

/*
PRE: Recibe el id (uint32_t) de la textura a agregar, y un puntero
unico a textura (std::unique_ptr<Texture>) de la textura a agregar.
POST: Agrega la textura recibida.
*/
void Window::add_texture(uint32_t id, std::unique_ptr<Texture> ptrTexture) {
    this->allTextures.insert(std::make_pair(id,std::move(ptrTexture)));
}

/*
Agrega el mapa de juego inicial, con todas sus texturas.
Levanta SdlError o OSError en caso de error.
*/
void Window::add_map(){
    float widthBlockMap = BLOCK_WIDTH;
    float heightBlockMap = BLOCK_HEIGHT;
    float xBlockFirst = -7.5;
    float xBlockLast = 9.5; 
    float yBlockFirst = 0.5;
    float yBlockLast = 8.5;
    float xBlock, yBlock;
    float manyBlocksHorizontal = xBlockLast - xBlockFirst + widthBlockMap;
    float manyBlocksVertical = yBlockLast - yBlockFirst + heightBlockMap;
    uint32_t id = this->idMainTexture;
    ++id;
    // Agrego techo
    for (float i = 0; i < manyBlocksHorizontal ; ++i){
        xBlock = i + xBlockFirst;
        yBlock = yBlockLast;
        this->add_block_metal_texture(id, Area(xBlock, yBlock, 
                                                widthBlockMap, 
                                                heightBlockMap));
        ++id;
    }
    manyBlocksVertical--;
    yBlockLast -= heightBlockMap;
    // Agrego piso
    for (float i = 0; i < manyBlocksHorizontal; ++i){
        xBlock = i + xBlockFirst;
        yBlock = yBlockFirst;
        this->add_block_metal_texture(id, Area(xBlock, yBlock, 
                                                widthBlockMap, 
                                                heightBlockMap));
        ++id;
    }
    manyBlocksVertical--;
    yBlockFirst += heightBlockMap;
    // Agrego lado izquierdo
    for (float i = 0; i < manyBlocksVertical; ++i){
        xBlock = xBlockFirst;
        yBlock = i + yBlockFirst;
        this->add_block_metal_texture(id, Area(xBlock, yBlock, 
                                                widthBlockMap, 
                                                heightBlockMap));
        ++id;
    }
    // Agrega lado derecho
    for (float i = 0; i < manyBlocksVertical; ++i){
        xBlock = xBlockLast;
        yBlock = i + yBlockFirst;
        this->add_block_metal_texture(id, Area(xBlock, yBlock, 
                                                widthBlockMap, 
                                                heightBlockMap));
        ++id;
    }

    Area areaChellMap(0.5, 1.75, CHELL_WIDTH, CHELL_HEIGHT);
    this->add_chell_texture(this->idMainTexture,areaChellMap);
}

/*
PRE: Recibe:
    La longitud y altura del ventanta en pixeles (ambos int).
    La longitud de la ventana en la medida en que se ubican y 
    dimensionan los objetos del mapa representados en la 
    primera.
POST: Inicializa una ventana de las medidas recibidas.
Levanta SDLException en caso de error.
*/
/*
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
*/
/*
PRE: Recibe:
    La longitud y altura del ventanta en pixeles (ambos int).
    El id de la textura en la que se centrara e indicarara que mostrar 
    en la ventana.
POST: Inicializa una ventana de las medidas recibidas.
Levanta SDLException en caso de error.
*/
Window::Window(int width, int height, uint32_t idMainTexture)
: width(width), height(height), idMainTexture(idMainTexture) {
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
    this->add_map();
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
    Texture & mainTexture = *(this->allTextures.at(this->idMainTexture));
    Area areaCamera = mainTexture.getVisionArea();
    float adjuster = this->width/areaCamera.getWidth();
    for (int i = 0; i < this->ids.size(); ++i){
        uint32_t actualId = this->ids[i];
        Texture & actualTexture = *(this->allTextures.at(actualId));
        actualTexture.render(adjuster, areaCamera);
    }
    SDL_RenderPresent(this->renderer);
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
/*
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
*/

/*
PRE: Recibe :
    El id (uint32_t) de indentificacion del bloque de metal a agregar.
    El area (Area) con las coordenadas y dimensiones del objeto
    que representa la textura en el mapa de juego (en unidades de 
    distancia del juego).
POST: Agrega un nueva textura de bloque de metal a la ventana, bajo las 
condiciones anteriores.
Levanta SdlException en caso de error.
*/
void Window::add_block_metal_texture(uint32_t id, Area areaMap){
    this->add_id_texture(id);
    this->add_big_texture(ALL_BLOCKS_SPRITES);
    std::unique_ptr<Texture> ptrTexture(
                                    new BlockMetalTexture(
                                        this->bigTextures.at(
                                            ALL_BLOCKS_SPRITES
                                        ), 
                                        areaMap
                                    )
                                );
    this->add_texture(id, std::move(ptrTexture));
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
    this->add_id_texture(id);
    this->add_big_texture(ALL_CHELL_SPRITES_PART_1);
    std::unique_ptr<Texture> ptrTexture(
                                    new ChellTexture(
                                        this->bigTextures.at(
                                            ALL_CHELL_SPRITES_PART_1
                                        ), 
                                        areaMap
                                    )
                                );
    this->add_texture(id, std::move(ptrTexture));
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
    Texture & textureOfId = *(this->allTextures.at(id));
    textureOfId.move_to(x,y);
}

/*
Devuelve una referencia constante al area (const Area &) 
de la textura de Chell principal de la ventana.
*/
const Area Window::getMainTextureArea() {
    return (*(this->allTextures.at(this->idMainTexture))).getAreaMap();
}