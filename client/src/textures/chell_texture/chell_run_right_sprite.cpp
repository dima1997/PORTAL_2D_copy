#include "../../../includes/textures/chell_texture/chell_run_right_sprite.h"

ChellRunRightSprite::ChellRunRightSprite() {}
ChellRunRightSprite::~ChellRunRightSprite() = default;

/*
Devuelve un sprite dinamico de chell 
corriendo a derecha.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellRunRightSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {1,2542},
                {196,2542},
                {391,2542},
                {586,2542},
                {781,2542},
                {976,2542},
                {1171,2542},
                {1366,2542},
                {1,2747},
                {196,2747},
                {391,2747},
                {586,2747}
            },
            194, 204
        )
    );
} 