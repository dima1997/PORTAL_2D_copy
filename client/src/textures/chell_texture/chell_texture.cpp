#include "../../../includes/textures/chell_texture/chell_texture.h"

#include "../../../includes/textures/chell_texture/chell_sprite_strategy.h"
#include "../../../includes/textures/chell_texture/move_sense.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/renderizable.h"
#include "../../../includes/textures/common_texture/movable.h"

#include <map>

/*
PRE: Recibe :
    Una referencia a la gran textura con todos los sprites de Chell.
    El area con las coordenadas y dimensiones de la localizacion de 
    Chell en el mapa de juego.
POST: Inicializa una textura dinamica de Chell.
*/
ChellTexture::ChellTexture(BigTexture &bigTextureChell, Area areaMap) 
:   bigTexture(bigTextureChell),
    areaMap(std::move(areaMap))
    {}

/*Destruye la textura dinamica de Chell.*/
ChellTexture::~ChellTexture() {}

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
    this->moveSense.move(xBefore, yBefore, xNow, yNow);
    this->spriteStrategy.move(xBefore, yBefore, xNow, yNow);
    
}   

/*
PRE: Recibe un factor de ajuster para redimensionar el area 
de mapa que ocupa de Chell, a pixeles.
POST: Renderiza la textura de Chell.
*/
void ChellTexture::render(float adjuster) {
    Area src = this->spriteStrategy.getNextArea(); 
    Area dest = this->areaMap.adjust(adjuster);
    this->moveSense.render(this->bigTexture, src, dest);
}
