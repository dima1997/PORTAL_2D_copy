#include "../../../includes/textures/block_metal_texture/block_metal_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

BlockMetalSprite::BlockMetalSprite() {}
BlockMetalSprite::~BlockMetalSprite() = default;

/*
Devuelve un sprite dinamico de bloque de metal.
IMAGE_PATH : ALL_BLOCKS_SPRITES
*/
DynamicSprite BlockMetalSprite::get_sprite(){
    return DynamicSprite({{401,18}},193,193);
} 
