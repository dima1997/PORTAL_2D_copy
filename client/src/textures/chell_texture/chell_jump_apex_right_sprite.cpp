#include "../../../includes/textures/chell_texture/chell_jump_apex_right_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

ChellJumpApexRightSprite::ChellJumpApexRightSprite() {}
ChellJumpApexRightSprite::~ChellJumpApexRightSprite() {}

/*
Devuelve un sprite dinamico de chell saltando 
verticalmente a derecha.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellJumpApexRightSprite::get_sprite(){
    return DynamicSprite({{1,21}},137, 207);
}