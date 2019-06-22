#include "../../../includes/textures/chell_texture/chell_sweat_right_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

ChellSweatRightSprite::ChellSweatRightSprite() {}
ChellSweatRightSprite::~ChellSweatRightSprite() = default;

/*
Devuelve un sprite dinamico de Chell 
sudando hacia la derecha.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellSweatRightSprite::get_sprite(){
    return DynamicSprite(
            {
                {1,4993},
                {217,4993},
                {433,4993},
                {649,4993},
                {865,4993},
                {1081,4993},
                {1297,4993},
                {1,5219},
                {217,5219},
                {433,5219},
                {649,5219},
                {865,5219},
                {1081,5219},
            },
            215, 225
        );
} 
