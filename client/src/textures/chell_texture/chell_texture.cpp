#include "../../../includes/textures/chell_texture/chell_texture.h"

#include "../../../includes/textures/chell_texture/chell_sprite_strategy.h"
#include "../../../includes/textures/chell_texture/move_sense.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/null_sprite.h"

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
    Una referencia a la gran textura con todos los sprites de Chell.
    El area con las coordenadas y dimensiones de la localizacion de 
    Chell en el mapa de juego.
POST: Inicializa una textura dinamica de Chell.
*/
ChellTexture::ChellTexture(BigTexture &bigTextureChell, Area areaMap) 
:   Texture(
        bigTextureChell, 
        std::move(areaMap),
        std::move(std::unique_ptr<SpriteStrategy>(new ChellSpriteStrategy())) 
    ) {
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
    (*this->ptrSpriteStrategy).move(xBefore, yBefore, xNow, yNow);
    this->moveSense.move(xBefore, yBefore, xNow, yNow);
}   

/*
PRE: Recibe un factor de ajuster para redimensionar el area 
de mapa que ocupa de Chell, a pixeles.
POST: Renderiza la textura de Chell.
*/
void ChellTexture::render(float adjuster, const Area & areaCamera) {
    // Necesitamos alternar el sprite de cualquier forma
    Area src = (*this->ptrSpriteStrategy).getNextArea();
    // Solo renderizamos si la texture esta en el area de la camara
    if (! this->areaMap.isIntersectedBy(areaCamera)){
        return;
    }
    Area dest = this->getAreaDest(adjuster, areaCamera);
    this->moveSense.render(this->bigTexture, src, dest);
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