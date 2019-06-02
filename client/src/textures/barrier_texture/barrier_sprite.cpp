#include "../../../includes/textures/barrier_texture/barrier_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Iniciliza un sprite de barrera que se 
encuentra en la imagen BARRIER_SPRITE de 
images_paths.h .
*/
BarrierSprite::BarrierSprite()
:   DynamicSprite(
        {
            {0,0}
        },
        135,6
    )
    {}

/*Destrue el sprite de barrera.*/
BarrierSprite::~BarrierSprite() = default;
