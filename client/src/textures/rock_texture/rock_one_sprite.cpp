#include "../../../includes/textures/rock_texture/rock_one_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Iniciliza un sprite de roca de tipo 1 que se 
encuentra en la imagen ROCKS_AND_BALLS_SPRITE de 
images_paths.h .
*/
RockOneSprite::RockOneSprite()
:   DynamicSprite(
        {
            {517,4513}
        },
        85,83
    )
    {}
/*Destrue el sprite de la roca de tipo 1.*/
RockOneSprite::~RockOneSprite() = default;

DynamicSprite RockOneSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {517,4513}
            },
            85,83
        )
    );
}