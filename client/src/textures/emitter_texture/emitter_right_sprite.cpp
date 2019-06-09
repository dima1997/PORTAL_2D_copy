#include "../../../includes/textures/emitter_texture/emitter_right_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Inicializa un sprite de bloque emisor hacia 
derecha que se encuentra en la imagen 
ALL_BLOCKS_SPRITES de images_paths.h .
*/
EmitterRightSprite::EmitterRightSprite()
:   DynamicSprite(
        {
            {1,1028}
        },
        193,193
    )
    {}
/*Destruye el sprite de bloque emisor hacia derecha.*/
EmitterRightSprite::~EmitterRightSprite() = default;

DynamicSprite EmitterRightSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {1,1028}
            },
            193,193
        )
    );
} 