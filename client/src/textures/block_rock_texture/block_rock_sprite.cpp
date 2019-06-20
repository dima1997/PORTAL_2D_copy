#include "../../../includes/textures/block_rock_texture/block_rock_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

BlockRockSprite::BlockRockSprite(){}

BlockRockSprite::~BlockRockSprite() = default;

/*
Devuelve un sprite dinamico de bloque de roca.
IMAGE_PATH : ALL_BLOCKS_SPRITES
*/
DynamicSprite BlockRockSprite::get_sprite(){
    return std::move(DynamicSprite({{201,18}},193,193));
}
