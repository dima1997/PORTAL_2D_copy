#include "../../../includes/textures/block_metal_texture/block_metal_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Iniciliza un sprite de bloque de metal estatico que se 
encuentra en la imagen all_blocks.png .
*/
BlockMetalSprite::BlockMetalSprite()
:   DynamicSprite(
        {
            {1,600}
        },
        193,193
    )
    {}
/*Destrue el sprite de bloque de metal estatico.*/
BlockMetalSprite::~BlockMetalSprite() = default;
