#include "../../../includes/textures/background_texture/background_one_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Iniciliza un sprite de fondo 1 que se 
encuentra en la imagen BACKGROUND de 
images_paths.h .
*/
BackgroundOneSprite::BackgroundOneSprite()
:   DynamicSprite(
        {
            {0,0}
        },
        880,452
    )
    {}

/*Destruye el sprite de fondo 1.*/
BackgroundOneSprite::~BackgroundOneSprite() = default;

DynamicSprite BackgroundOneSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {0,0}
            },
            //880,452 // 0
            //1920,1080 // 1 y 2
            900, 550 // 3
        )
    );
} 
