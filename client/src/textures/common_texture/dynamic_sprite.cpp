#include "../../../includes/textures/common_texture/dynamic_sprite.h"

#include "../../../includes/textures/common_texture/area.h"

#include <vector>

DynamicSprite::DynamicSprite()
:   spritesCoordTape(), 
    width(0), 
    height(0) {}

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
:   spritesCoordTape(spritesCoordTape), 
    width(width), 
    height(height), 
    index(0), 
    reverse(false) {}

/*Destruye el sprite dinamico.*/
DynamicSprite::~DynamicSprite(){}

/*Constructor por copia*/
DynamicSprite::DynamicSprite(const DynamicSprite & other)
:   spritesCoordTape(other.spritesCoordTape),
    width(other.width),
    height(other.height),
    index(other.index),
    reverse(other.reverse) {}

/*Asignacion por copia.*/
DynamicSprite & DynamicSprite::operator=(const DynamicSprite & other){
    if (this == & other){
        return *this;
    }
    this->spritesCoordTape = other.spritesCoordTape;
    this->width = other.width;
    this->height = other.height;
    this->index = other.index;
    this->reverse = other.reverse;
    return *this;
}

/*Constructor por movimiento.*/
DynamicSprite::DynamicSprite(DynamicSprite && other)
:   spritesCoordTape(std::move(other.spritesCoordTape)){
    this->width = other.width;
    this->height = other.height;
    this->index = other.index;
    this->reverse = other.reverse;
    other.width = 0;
    other.height = 0;
    other.index = 0;
    other.reverse = false;
}

/*Asignacion por movimiento.*/
DynamicSprite & DynamicSprite::operator=(DynamicSprite && other){
    if (this == & other){
        return *this;
    }
    this->spritesCoordTape = std::move(other.spritesCoordTape);
    this->width = other.width;
    this->height = other.height;
    this->index = other.index;
    this->reverse = other.reverse;
    other.width = 0;
    other.height = 0;
    other.index = 0;
    other.reverse = false;
    return *this;
}

/*
Devuelve un area (Area) con las coordenadas y dimensiones del proximo a sprite a 
ser usado.
*/
Area DynamicSprite::getNextArea(){
    float xCoord = this->spritesCoordTape[this->index].first;
    float yCoord = this->spritesCoordTape[this->index].second;
    if (this->reverse){
        --index;
    } else {
        ++index;
    }
    index = index % this->spritesCoordTape.size();
    return std::move(Area(xCoord, yCoord, this->width, this->height));
}

/*
Reinicia el ciclo de sprites al sprite inicial,
segun su orden interno.
*/
void DynamicSprite::restart(){
    if (this->reverse){
        this->index = this->spritesCoordTape.size()-1;
    } else {
        this->index = 0;
    }
}

/*
Devuelve true, si el sprite actual es el ultimo 
sprite de la tira de sprites que los constituyen; 
false en caso contrario.
*/
bool DynamicSprite::is_last_sprite(){
    if (this->reverse){
        return this->index <= 0;
    }
    return ((this->index + 1) >= this->spritesCoordTape.size());
}

/*
Invierte el orden en que se muetran los sprites, 
empezando por el ultimo, y terminando por el primero.
*/
void DynamicSprite::reverse_sprite(){
    this->reverse = true;
}