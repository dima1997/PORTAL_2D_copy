#include "../../../includes/textures/barrier_texture/barrier_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

BarrierSprite::BarrierSprite() {}
BarrierSprite::~BarrierSprite() = default;

/*
Devuelve un sprite dinamico de 
barrera de energia.
IMAGE_PATH : BARRIER_SPRITES
*/
DynamicSprite BarrierSprite::get_sprite(){
    return DynamicSprite({{0,0}},135,6);
} 