#include "../../../includes/textures/triangle_texture/triangle_botom_left_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

TriangleBotomLeftSprite::TriangleBotomLeftSprite() {}
TriangleBotomLeftSprite::~TriangleBotomLeftSprite() = default;

/*
Devuelve un sprite dinamico de triangulo rectangulo 
en la esquina inferior izquierda.
IMAGE_PATH : ALL_BLOCKS_SPRITES 
*/
DynamicSprite TriangleBotomLeftSprite::get_sprite(){
    return std::move(DynamicSprite({{804,18}},188,178));
} 
