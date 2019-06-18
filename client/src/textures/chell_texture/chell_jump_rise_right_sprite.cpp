#include "../../../includes/textures/chell_texture/chell_jump_rise_right_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

ChellJumpRiseRightSprite::ChellJumpRiseRightSprite() {}
ChellJumpRiseRightSprite::~ChellJumpRiseRightSprite() = default;

/*
Devuelve un sprite dinamico de chell 
saltando hacia la derecha.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellJumpRiseRightSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {1,855},
                {145,855},
                {289,855},
                {433,855}
            },
            143, 228
        )
    );
}