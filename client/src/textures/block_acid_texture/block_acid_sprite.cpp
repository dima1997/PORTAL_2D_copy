#include "../../../includes/textures/block_acid_texture/block_acid_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Inicializa un sprite de bloque de acido estatico que se 
encuentra en la imagen ALL_BLOCKS_SPRITES de images_paths.h .
*/
BlockAcidSprite::BlockAcidSprite()
:   DynamicSprite(
        {
            {1,172}
        },
        193,193
    )
    {}
/*Destruye el sprite de bloque de acido estatico.*/
BlockAcidSprite::~BlockAcidSprite() = default;
