#include "../../../includes/textures/background_texture/background_one_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

BackgroundOneSprite::BackgroundOneSprite() {}
BackgroundOneSprite::~BackgroundOneSprite() = default;


/*
Devuelve un sprite dinamico de 
fondo de pantalla 1.
IMAGE_PATH : BACKGROUND_SPRITES
*/
DynamicSprite BackgroundOneSprite::get_sprite(){
    return DynamicSprite({{0,0}},900, 550);
} 
