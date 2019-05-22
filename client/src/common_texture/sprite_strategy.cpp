#include "sprite_strategy.h"

#include "dynamic_sprite.h"
#include "area.h"

/*
PRE: Recibe un puntero unico a un sprite dinamico 
(std::unique_ptr<DynamicSprite>), por movimiento 
semantico.
POST: Inicializa un SpriteStrategy que alterna los 
sprites del DynamicSprite recibido, uno a uno.
*/
SpriteStrategy::SpriteStrategy(std::unique_ptr<DynamicSprite> ptrDynamicSprite)
: ptrDynamicSprite(std::move(ptrDynamicSprite)) {}

/*Destruye el sprite strategy.*/
SpriteStrategy::~SpriteStrategy() = default;

/*
PRE: Recibe :
    las coordenadas anteriores (int) x,y de la textura que representa.
    las coordenadas nuevas (int) x,y de la textura que representa.
POST: No hace nada.
*/
void move(float xBefore, float yBefore, float xNow, float yNow) {}

/*No hace nada.*/
void switch() {}

/*
Devuelve el area correspondiente al siguiente sprite de la textura que 
representa, en la imagen.png correspondiente.
*/
Area getNextArea(){
    DynamicSprite & actualSprite = *(this->ptrDynamicSprite);
    return std::move(actualSprite.getNextArea());
}