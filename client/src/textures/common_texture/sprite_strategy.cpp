#include "../../../includes/textures/common_texture/sprite_strategy.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"
#include "../../../includes/textures/common_texture/area.h"

#include <memory>

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
void SpriteStrategy::move(float xBefore, float yBefore, float xNow, float yNow) {}

/*No hace nada.*/
void SpriteStrategy::switch_sprite() {}

/*
Devuelve el area correspondiente al siguiente sprite de la textura que 
representa, en la imagen.png correspondiente.
*/
Area SpriteStrategy::getNextArea(){
    DynamicSprite & actualSprite = *(this->ptrDynamicSprite);
    return std::move(actualSprite.getNextArea());
}