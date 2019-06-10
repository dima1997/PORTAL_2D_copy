#include "../../../includes/textures/chell_texture/chell_dead_strategy.h"

#include "../../../includes/textures/chell_texture/chell_dying_sprite.h"

#include "../../../includes/textures/common_texture/null_sprite.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/area.h"

#include "../../../includes/mixer/sounds_path.h"

/*Inicializa el estado de sprite de Chell muerta.*/
ChellDeadStrategy::ChellDeadStrategy()
:   SpriteStrategy(ChellDyingSprite::get_sprite()),
    spriteName(DYING) {}

/*Destruye el estado de sprite de Chell muerta*/
ChellDeadStrategy::~ChellDeadStrategy() = default;

/*
Devuelve el area correspondiente al siguiente sprite 
de Chell muerta, en la imagen ALL_CHELL_SPRITES de 
images_path.h .
*/
Area ChellDeadStrategy::getNextArea(){
    if (this->spriteName != DEAD){
        if (this->dynamicSprite.is_last_sprite()) { 
            this->dynamicSprite = NullSprite::get_sprite();
        }
    }
    return std::move(this->dynamicSprite.getNextArea());
}