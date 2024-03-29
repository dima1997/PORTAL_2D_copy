#include "../../../includes/textures/common_texture/texture.h"

#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h" 
#include "../../../includes/textures/common_texture/dynamic_sprite.h"
#include "../../../includes/mixer/mixer.h" 

#include <memory>

/*
Pre: Recibe un factor de ajuste (pixeles/<unidad de mapa>), 
y una referencia constante al area de la camara en el mapa 
(en unidades y sistema de referencia del mapa) de juego, 
que indica que objetos del mismo se visualizan en la 
ventana.
POST: Devuelve el area de destino de la textura, en la ventana, 
con respecto a la misma.
*/
Area Texture::getAreaDest(float adjuster, const Area & areaCamera) {
    Area areaCameraTopLeft = areaCamera.from_center_to_top_left(); 
    Area dest = this->areaMap.from_center_to_top_left();
    dest = dest.to_y_axis_down_reference_system(
                    areaCameraTopLeft.getX(), areaCameraTopLeft.getY());
    dest = dest.adjust(adjuster);
    return dest;
}

/*
PRE: Recibe:
    una referencia a una gran textura que 
    contiene la imagen donde se encuentra el/los sprite/s 
    que utiliza la textura; 
    el area (Area) que ocupa el objeto que representa la 
    textura en el mapa de juego;
    un puntero unico con el sprite strategy que utiliza 
    la textura para ir variando sus sprites;
    un angulo con el que rotar el sprite;
    tres modularizadores del color RGB, los cuales 
    multiplican al a cada color del patron por si mismos
    sobre 255.
POST: Inicializa una textura.
*/

Texture::Texture(
    BigTexture & bigTexture, 
    Area & areaMap, 
    std::unique_ptr<SpriteStrategy> ptrSpriteStrategy,
    double angle,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
:   bigTexture(bigTexture), 
    areaMap(areaMap), 
    ptrSpriteStrategy(std::move(ptrSpriteStrategy)),
    following(false),
    ptrFollowArea(NULL),
    angle(angle),
    redMod(redMod),
    greenMod(greenMod),
    blueMod(blueMod),
    flip(NO_FLIP) {}

/*
PRE: Recibe:
    una referencia a una gran textura que 
    contiene la imagen donde se encuentra el/los sprite/s 
    que utiliza la textura; 
    el area (Area) que ocupa el objeto que representa la 
    textura en el mapa de juego;
    el sprite dinamico que sera el unico sprite a usar en la
    vida de la textura;
    un angulo (double) para rotar la textura al renderizarla;
    tres modularizadores del color RGB, los cuales 
    multiplican al a cada color del patron por si mismos
    sobre 255.
POST: Inicializa una textura.
*/
Texture::Texture(
    BigTexture & bigTexture, 
    Area & areaMap, 
    const DynamicSprite & dynamicSprite,
    double angle,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
:   bigTexture(bigTexture), 
    areaMap(areaMap),
    ptrSpriteStrategy(new SpriteStrategy(dynamicSprite)),
    following(false),
    ptrFollowArea(NULL),
    angle(angle),
    redMod(redMod),
    greenMod(greenMod),
    blueMod(blueMod),
    flip(NO_FLIP)
    {}

/*Destruye la textura.*/
Texture::~Texture() = default;

/*
PRE: Recibe la coordenadas (float) x,y donde se desplaza 
la textura.
POST: Desplaza la textura al posicion indicada, y realiza
cambios en su sprite segun indique el sprite strategy con 
que se creo.
*/
void Texture::move_to(float x, float y){
    float xBefore = this->areaMap.getX();
    float yBefere = this->areaMap.getY();
    float xNow = x;
    float yNow = y;
    this->areaMap.setX(xNow);
    this->areaMap.setY(yNow);
    (*this->ptrSpriteStrategy).move(xBefore, yBefere, xNow, yNow, this->sounds);
}

/*
Realiza un switch en su sprite actual, segun el sprite 
strategy con que se creo.
*/
void Texture::switch_sprite(){
    (*this->ptrSpriteStrategy).switch_sprite();
}

/*
Pre: Recibe un factor de ajuste (pixeles/<unidad de mapa>), 
y una referencia constante al area de la camara en el mapa 
(en unidades y sistema de referencia del mapa) de juego, 
que indica que objetos del mismo se visualizan en la 
ventana.
POST: Renderiza la textura si es que alguna parte de la misma 
se encuentra en el area de la camera recibida, ajustando las 
dimensiones de la textura a pixeles, con el factor recibido.
*/
void Texture::render(float adjuster, const Area & areaCamera) {
    Area src = (*this->ptrSpriteStrategy).getNextArea();
    if (! this->areaMap.isIntersectedBy(areaCamera)){
        return;
    }
    if (this->following) {
        this->areaMap.setX(this->ptrFollowArea->getX());
        this->areaMap.setY(this->ptrFollowArea->getY());
    }
    Area dest = this->getAreaDest(adjuster, areaCamera);
    this->bigTexture.render(
        src, 
        dest, 
        this->flip, 
        this->angle,
        this->redMod,
        this->greenMod,
        this->blueMod
    );
}

/*
Retorna un area (Area) de vision nula.
*/
Area Texture::getVisionArea() {
    return Area(0,0,0,0);
}

/*
Devuelve una referencia constante al area (const Area &) de la 
textura en el mapa del juego.
*/
const Area & Texture::get_area_map(){
    return this->areaMap;
}

/*
Reproduce los sonidos que la textura tiene guardada. 
*/
void Texture::sound(Mixer & mixer) {
    for (auto it = this->sounds.begin(); it != this->sounds.end(); ) {
        mixer.play_chunck(SOUNDS_PATH.at(*it));   
        it = this->sounds.erase(it);
    }
}

/*
PRE: Recibe una referencia constante a un area (const Area &).
POST: Ahora el area del mapa de esta textura, copia las 
coordenadas del area recibida, cada vez que se renderiza.
*/
void Texture::follow_area(const Area & areaMap) {
    this->ptrFollowArea = & areaMap;
    this->following = true;
}

/*Deja de seguir al area que sigue.*/
void Texture::stop_follow() {
    this->ptrFollowArea = NULL;
    this->following = false;
}

/*Actualiza la textura.*/
void Texture::update(){
    this->ptrSpriteStrategy->update();
}

/*
PRE: Recibe las coordenadas (float) x,y 
a donde apunta la textura
POST: Apunta en la direccion indicada.
*/
void Texture::point_to(float x, float y){
    this->ptrSpriteStrategy->point(
        this->areaMap.getX(), 
        this->areaMap.getY(),
        x,
        y
    );
}