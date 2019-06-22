#include "../../../includes/textures/chell_texture/chell_cake_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

#include <vector>

/*
Devuelve un sprite dinamico de Chell comiendo 
torta.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellCakeSprite::get_sprite(){
    return DynamicSprite({
            {1,469},
            {118,469},
            {235,469},
        },
        116,145
    );
}
