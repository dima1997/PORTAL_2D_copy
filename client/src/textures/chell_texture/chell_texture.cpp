#include "../../../includes/textures/chell_texture/chell_texture.h"

#include "../../../includes/textures/chell_texture/chell_sprite_strategy.h"
#include "../../../includes/textures/chell_texture/chell_dead_strategy.h"
#include "../../../includes/textures/chell_texture/chell_cake_sprite.h"
#include "../../../includes/textures/chell_texture/chell_dying_sprite.h"
#include "../../../includes/textures/chell_texture/move_sense.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/null_sprite.h"
#include "../../../includes/textures/common_texture/null_end_strategy.h"


#include <map>

#define VISION_AREA_METER_WIDTH 10;
#define VISION_AREA_METER_HEIGHT 8;

/*Actualiza el area de vision de Chell.*/
void ChellTexture::updateVisionArea(){
    float xVision = this->areaMap.getX();
    float yVision = this->areaMap.getY();
    float widthVision = VISION_AREA_METER_WIDTH;
    float heightVision = VISION_AREA_METER_HEIGHT;
    this->areaVision = Area(xVision, yVision, widthVision, heightVision);
}

/*
PRE: Recibe :
    Una referencia a la gran textura con todos los sprites de Chell;
    El area con las coordenadas y dimensiones de la localizacion de 
    Chell en el mapa de juego;
    Tres modificadores de color RGB (uint8_t) (mayores a cero, y 
    menores a 256). 
POST: Inicializa una textura dinamica de Chell.
*/
ChellTexture::ChellTexture(
    BigTexture & bigTextureChell, 
    Area & areaMap, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
) 
:   Texture(
        bigTextureChell, 
        areaMap,
        std::move(std::unique_ptr<SpriteStrategy>(new ChellSpriteStrategy())),
        0,
        redMod,
        greenMod,
        blueMod 
    ),
    status(CHELL_STATUS_ALIVE) {
    this->updateVisionArea();
}

/*Destruye la textura dinamica de Chell.*/
ChellTexture::~ChellTexture() = default;

/*
PRE: Recibe una nueva coordenada (float) x,y .
POST: Mueve la textura de Chell a la coordenada 
indicada.
*/
void ChellTexture::move_to(float x, float y) {
    float xBefore = this->areaMap.getX();
    float yBefore = this->areaMap.getY();
    float xNow = x;
    float yNow = y;
    this->areaMap.setX(xNow);
    this->areaMap.setY(yNow);
    (*this->ptrSpriteStrategy).move(xBefore, yBefore, xNow, yNow, 
                                    this->sounds);
    this->flip = this->moveSense.update(xBefore, xNow);
}   

/*
Alterna entre Chell viva y muerta.
*/
void ChellTexture::switch_sprite(){
    if (this->status == CHELL_STATUS_ALIVE){
        this->ptrSpriteStrategy.reset(new NullEndStrategy(
            ChellDyingSprite::get_sprite()
        ));
        this->sounds.push_back(SOUND_DYING);
        this->status = CHELL_STATUS_DEAD;
        return;
    }
    if (this->status == CHELL_STATUS_DEAD){
        this->ptrSpriteStrategy.reset(new NullEndStrategy(
            ChellCakeSprite::get_sprite()
        ));
        this->status = CHELL_STATUS_CAKE;
        return;
    }
}

/*
Devuelve el area de vision actual del 
Chell en el mapa de juego.
*/
Area ChellTexture::getVisionArea() {
    this->updateVisionArea();
    Area areaVisionCopy = this->areaVision;
    return std::move(areaVisionCopy);
}

/*
PRE: Recibe las coordenadas (float) x,y 
a donde apunta la textura
POST: Apunta en la direccion indicada.
*/
void ChellTexture::point_to(float x, float y) {
    this->ptrSpriteStrategy->point(
        this->areaMap.getX(),
        this->areaMap.getY(),
        x,
        y
    );
    this->flip = this->moveSense.update(this->areaMap.getX(), x);
}