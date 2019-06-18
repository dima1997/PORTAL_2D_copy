#include "../../../includes/textures/cake_texture/cake_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

CakeSprite::CakeSprite() {}
CakeSprite::~CakeSprite() = default;

/*
Devuelve un sprite dinamico de torta.
IMAGE_PATH : CAKE_SPRITES
*/
DynamicSprite CakeSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {6,6},
                {92,6},
                {179,6},
                {275,6},
                {362,6},
                {448,6},
                {534,6},
                {620,6}
            },
            84,78
        )
    );
}
