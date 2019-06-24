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

#include <iostream>

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
Window::Window(
    int width, 
    int height, 
    uint32_t idMainTexture, 
    YAML::Node & mapConfig
)
:   videoWidth(width), 
    videoHeight(height), 
    idMainTexture(idMainTexture),
    isRecording(false) 
{
    this->init_window();
    this->init_renderer();
    this->init_video_record();

    MapCreator mapCreator(mapConfig,*this);
    mapCreator.add_map(); 
    {
        std::unique_lock<std::mutex> l(this->mutex);
        Texture & mainTexture = *(this->allTextures.at(this->idMainTexture));
        this->areaCamera = mainTexture.getVisionArea(); 
    }
}

/*
PRE: Las dimensiones del video ya fueron 
inicializadas.
POST: Inicializa la ventana.
*/
void Window::init_window(){
    this->window = SDL_CreateWindow(
        "Portal Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        this->videoWidth,
        this->videoHeight,
        SDL_WINDOW_RESIZABLE
    );
    if (this->window == NULL){
        throw SdlException("Error al crear ventana.", SDL_GetError());
    }
}

/*
PRE: SDL_window fue inicializado.
POST: Inicializa el renderer.
*/
void Window::init_renderer(){
    this->renderer = SDL_CreateRenderer(
        this->window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (this->renderer == NULL) {
        SDL_DestroyWindow(this->window);
        throw SdlException("Error al crear renderizador.", SDL_GetError());   
    }
}

/*
PRE: SDL_window y SDL_Renderer ya fueron 
inicializados.
POST: Inicializa los atributos de para 
grabar video.
*/
void Window::init_video_record(){
    this->videoTexture = SDL_CreateTexture(
        this->renderer,
        SDL_PIXELFORMAT_RGB24, 
        SDL_TEXTUREACCESS_TARGET, 
        this->videoWidth, 
        this->videoHeight
    );
    if (! this->videoTexture){
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        throw SdlException(
            "On Window: initialization of video texture failed.",
            SDL_GetError()
        );
    
    }
}

/*Destruye la ventana.*/
Window::~Window() {
    if (this->videoTexture){
        SDL_DestroyTexture(this->videoTexture);
        this->videoTexture = nullptr;
    }
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
void Window::render(std::vector<char> & videoFrameBuffer) {
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
    {
        std::unique_lock<std::mutex> l(this->mutex);
        this->areaCamera = newAreaCamera;
    }

    SDL_SetRenderTarget(this->renderer, NULL);
    this->_render(adjuster, newAreaCamera);
    if (this->is_recording()){
        SDL_SetRenderTarget(this->renderer, this->videoTexture); 
        this->_render(adjuster, newAreaCamera, this->idRecordTexture);
    }
    
    this->_update();

    SDL_RenderPresent(this->renderer);

    if (this->is_recording()){
        videoFrameBuffer.resize(this->videoWidth*this->videoHeight*3);
        int res = SDL_RenderReadPixels(
            this->renderer, 
            NULL, 
            SDL_PIXELFORMAT_RGB24, 
            videoFrameBuffer.data(), 
            this->videoWidth * 3
        );
        if (res) {
            throw SdlException("RendererReadPixels error", SDL_GetError());
        }
    }
}

/*
PRE: Recibe el factor de ajuste; y el area de la camara
que representa la ventana.
POST: Renderiza todas las texturas segun estos datos.
*/
void Window::_render(float adjuster, Area areaCamera){
    this->fill();
    for (int i = 0; i < (int)this->ids.size(); ++i){
        uint32_t actualId = this->ids[i];
        Texture & actualTexture = *(this->allTextures.at(actualId));
        actualTexture.render(adjuster, areaCamera);
    }
}

void Window::_render(float adjuster, Area areaCamera, uint32_t idNotRender){
    this->fill();
    for (int i = 0; i < (int)this->ids.size(); ++i){
        uint32_t actualId = this->ids[i];
        if (actualId == idNotRender){
            continue;
        }
        Texture & actualTexture = *(this->allTextures.at(actualId));
        actualTexture.render(adjuster, areaCamera);
    }
}

void Window::_update(){
    for (int i = 0; i < (int)this->ids.size(); ++i){
        uint32_t actualId = this->ids[i];
        Texture & actualTexture = *(this->allTextures.at(actualId));
        actualTexture.update();
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

/*
PRE: Recibe el id (uint32_t) de dos texturas en la ventana.
POST: Hace que la primera (idFollowing) se ponga a seguir 
a la segunda (idFollowed).
*/
void Window::start_follow(uint32_t idFollowing, uint32_t idFollowed){
    if (this->allTextures.count(idFollowing) == 0){
        std::stringstream errDescription; 
        errDescription << "No existe textura con id : " << idFollowing << ".";
        throw OSException("Error en ventana:",errDescription.str().c_str());
    } 
    if (this->allTextures.count(idFollowed) == 0){
        std::stringstream errDescription; 
        errDescription << "No existe textura con id : " << idFollowed << ".";
        throw OSException("Error en ventana:",errDescription.str().c_str());
    } 
    const Area & areaFollow = (this->allTextures.at(idFollowed))->get_area_map();
    (this->allTextures.at(idFollowing))->follow_area(areaFollow);
}

/*
PRE: Recibe el id de una textura en la ventana.
POST: Hace que la textura deje de seguir a cualquier
otra textura que este siguiendo.
*/
void Window::stop_follow(uint32_t idFollowing){
    if (this->allTextures.count(idFollowing) == 0){
        std::stringstream errDescription; 
        errDescription << "No existe textura con id : " << idFollowing << ".";
        throw OSException("Error en ventana:",errDescription.str().c_str());
    } 
    (this->allTextures.at(idFollowing))->stop_follow();
}

/*
Devuelve el id de la textura principal de la ventana.
*/
uint32_t Window::get_main_id(){
    return this->idMainTexture;
}

/*
PRE: Recibe un id de una textura en el ventana.
POST: Setea el id recibido como id de textura principal.
*/
void Window::set_main_id(uint32_t id){
    if (this->allTextures.count(id) == 0){
        std::stringstream errDescription; 
        errDescription << "No existe textura con id : " << id << ".";
        throw OSException("Error en ventana:",errDescription.str().c_str());
    } 
    this->idMainTexture = id;
}

/*
Devuelve true si la ventana esta grabando, 
false en caso contrario.
*/
bool Window::is_recording(){
    int actualWidth;
    int actualHeight;
    SDL_GetWindowSize(this->window,&actualWidth,&actualHeight);
    bool isWidthVideo = (this->videoWidth == actualWidth);
    bool isHeightVideo = (this->videoHeight == actualHeight);
    if (this->isRecording){
        if (isWidthVideo && isHeightVideo){
            return true;
        }
        this->record();
    }
    return false;
}

/*
Alterna entre grabando video y no haciendolo. 
Cuando se pone a grabar, lleva la ventana al 
modo de grabacion.
*/
void Window::record(){
    this->switch_texture(this->idRecordTexture);
    if (this->isRecording){
        this->isRecording = false;
        SDL_DisplayMode displayMode;
        SDL_GetCurrentDisplayMode(0, &displayMode);
        auto maxWidth = displayMode.w;
        auto maxHeight = displayMode.h;
        SDL_SetWindowMaximumSize(this->window, maxWidth, maxHeight);
        SDL_SetWindowMinimumSize(this->window, 0, 0);
    } else {
        this->isRecording = true;
        SDL_SetWindowSize(this->window, this->videoWidth, this->videoHeight);
        SDL_SetWindowMaximumSize(this->window, this->videoWidth, this->videoHeight);
        SDL_SetWindowMinimumSize(this->window, this->videoWidth, this->videoHeight);
        SDL_RestoreWindow(this->window);
    }
}

/*
PRE: Recibe el id de la textura utilizada 
para indicar grabacion.
POST: Setea el id de dicha textura.
*/
void Window::set_record_id(uint32_t id){
    this->idRecordTexture = id;
}

void Window::point_texture(uint32_t id, float x, float y){
    if (this->allTextures.count(id) == 0){
        std::stringstream errDescription; 
        errDescription << "No existe textura con id : " << std::dec << id << ".";
        throw OSException("Error en ventana:",errDescription.str().c_str());
    }
    Texture & textureOfId = *(this->allTextures.at(id));
    textureOfId.point_to(x,y);
}

void Window::set_loading_id(uint32_t id){
    this->idLoadingTexture = id;
}

void Window::switch_loading_texture(){
    this->switch_texture(this->idLoadingTexture);
}