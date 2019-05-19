#include "chell_texture.h"

#include "big_texture.h"
#include "chell_sprite_state.h"
#include "move_sense.h"
#include "area.h"
#include "renderizable.h"

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
PRE: Recibe una nueva coordenada x,y .
POST: Mueve la textura de Chell a la coordenada 
indicada.
*/
void ChellTexture::move_to(int x, int y) {
    float xBefore = this->areaMap.getX();
    float yBefore = this->areaMap.getY();
    float xNow = x;
    float yNow = y;
    this->areaMap.setX(xNow);
    this->areaMap.setY(yNow);
    this->moveSense.move(xBefore, yBefore, xNow, yNow);
    this->spriteState.move(xBefore, yBefore, xNow, yNow);
    
}   

/*
PRE: Recibe un factor de ajuster para redimensionar el area 
de mapa que ocupa de Chell, a pixeles.
POST: Renderiza la textura de Chell.
*/
void ChellTexture::render(float adjuster) {
    Area src = std::move(this->spriteState.getNextArea());
    Area dest = std::move(this->areaMap.adjust(adjuster));
    this->moveSense.render(this->bigTexture, src, dest);
}