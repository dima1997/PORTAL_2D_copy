#include "../../../includes/textures/common_texture/sprite_strategy.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"
#include "../../../includes/textures/common_texture/area.h"

#include "../../../includes/mixer/sounds_path.h"

#include <memory>

/*
PRE: Recibe un sprite dinamico 
POST: Inicializa un SpriteStrategy que alterna los 
sprites del DynamicSprite recibido, uno a uno.
*/
SpriteStrategy::SpriteStrategy(DynamicSprite dynamicSprite)
:   dynamicSprite(dynamicSprite) {}


/*Destruye el sprite strategy.*/
SpriteStrategy::~SpriteStrategy() = default;

/*
PRE: Recibe :
    las coordenadas anteriores (int) x,y de la textura que representa.
    las coordenadas nuevas (int) x,y de la textura que representa.
POST: No hace nada.
*/
void SpriteStrategy::move(float xBefore, float yBefore, float xNow, float yNow) {}

/*
PRE: Recibe :
    las coordenadas anteriores (int) x,y de la textura que representa.
    las coordenadas nuevas (int) x,y de la textura que representa.
    una referencia a un vector de nombre de sonidos.
POST: No hace nada.
*/
void SpriteStrategy::move(float xBefore, float yBefore, float xNow, float yNow, 
                          std::vector<SOUND_NAME> & sounds) {}

/*No hace nada.*/
void SpriteStrategy::switch_sprite() {}

/*
Devuelve el area correspondiente al siguiente sprite de la textura que 
representa, en la imagen.png correspondiente.
*/
Area SpriteStrategy::getNextArea(){
    return std::move(this->dynamicSprite.getNextArea());
}

/*Actualiza el sprite al siguiente.*/
void SpriteStrategy::update(){
    this->dynamicSprite.update();
}