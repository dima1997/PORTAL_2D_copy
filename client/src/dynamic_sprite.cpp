#include "dynamic_sprite.h"

#include "area.h"

#include <vector>

/*
PRE: Recibe un vector de coordenadas x,y (std::vector<std::pair<int, int>>) de
las esquinas superior izquierda de cada sprite a utilizar, en el orden a ser
alternados; el ancho y alto (int) de cada sprite del vector.
(Se supone que todos los sprites en el vector recibido tienen las misma 
dimension, en pixeles).
POST: Inicializa un sprite dinamico. 
*/
DynamicSprite::DynamicSprite(std::vector<std::pair<int, int>> spritesCoordTape,
                             int width, int height)
: spritesCoordTape(spritesCoordTape), width(width), height(height), indice(0) {}

/*Destruye el sprite dinamico.*/
DynamicSprite::~DynamicSprite(){}

/*
Devuelve un area (Area) con las coordenadas y dimensiones del proximo a sprite a 
ser usado.
*/
Area DynamicSprite::getNextArea(){
    float xCoord = this->spritesCoordTape[this->indice].first;
    float yCoord = this->spritesCoordTape[this->indice].second;
    ++indice;
    indice = indice % this->spritesCoordTape.size();
    return std::move(Area(xCoord, yCoord, this->width, this->height));
}

/*Reinicia el ciclo de sprites al sprite inicial.*/
void DynamicSprite::restart(){
    this->indice = 0;
}