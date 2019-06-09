#include "../../../includes/textures/block_rock_texture/block_rock_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Inicializa un sprite de bloque de piedra estatico que se 
encuentra en la imagen ALL_BLOCKS_SPRITES de images_paths.h .
*/
BlockRockSprite::BlockRockSprite()
:   DynamicSprite(
        {
            {1,386}
        },
        193,193
    )
    {}
/*Destruye el sprite de bloque de piedra estatico.*/
BlockRockSprite::~BlockRockSprite() = default;

DynamicSprite BlockRockSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {1,386}
            },
            193,193
        )
    );
}
