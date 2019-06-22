#include "../../../includes/textures/chell_texture/chell_jump_fall_right_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

ChellJumpFallRightSprite::ChellJumpFallRightSprite() {}
ChellJumpFallRightSprite::~ChellJumpFallRightSprite() = default;

/*
Devuelve un sprite dinamico de Chell 
cayendo hacia la derecha.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellJumpFallRightSprite::get_sprite(){
    return DynamicSprite(
        {
            {1,1835},
            {158,1835},
            {315,1835},
            {472,1835}
            
        },
        156, 217
    );
}