#include "../../../includes/textures/common_texture/sprite_creator.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
PRE: Recibe un sprite dinamico (DynamicSprite) 
POST: Inicializo un creador de sprites de dicho
sprite recido.
*/
SpriteCreator::SpriteCreator(DynamicSprite dynamicSprite)
:   dynamicSprite(dynamicSprite) {}

/*Destruye el creador de sprites dinamicos.*/
SpriteCreator::~SpriteCreator() = default;

/*Devuelve el sprite dynamico de este creador.*/
DynamicSprite SpriteCreator::get_sprite(){
    DynamicSprite copiaSprite = this->dynamicSprite;
    return std::move(copiaSprite);
}
