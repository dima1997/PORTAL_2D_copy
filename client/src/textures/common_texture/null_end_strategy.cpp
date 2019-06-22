#include "../../../includes/textures/common_texture/null_end_strategy.h"

#include "../../../includes/textures/common_texture/null_sprite.h"
#include "../../../includes/textures/common_texture/two_sprites_strategy.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/area.h"

/*
PRE: Recibe el sprite dinamico a usar como 
principal hasta que llegue a su sprite final. 
POST: Inicializa el strategy de sprite nulo.
*/
NullEndStrategy::NullEndStrategy(const DynamicSprite & mainSprite)
:   TwoSpritesStrategy(
        mainSprite, 
        NullSprite::get_sprite()
    ),
    spriteName(NOT_NULL_SPRITE) {}

/*Destruye el strategy de sprite nulo*/
NullEndStrategy::~NullEndStrategy() = default;

/*Actualiza el sprite al siguiente a usar.*/
void NullEndStrategy::update(){
    this->dynamicSprite.update();
    if (this->spriteName != NULL_SPRITE){
        if (this->dynamicSprite.is_last_sprite()) { 
            this->switch_sprite();
            this->spriteName = NULL_SPRITE;
        }
    }
}