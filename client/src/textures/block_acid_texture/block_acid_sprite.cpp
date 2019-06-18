#include "../../../includes/textures/block_acid_texture/block_acid_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

BlockAcidSprite::BlockAcidSprite() {}
BlockAcidSprite::~BlockAcidSprite() = default;

/*
Devuelve un sprite dinamico de bloque de acido.
IMAGE_PATH : ALL_BLOCKS_SPRITES
*/
DynamicSprite BlockAcidSprite::get_sprite(){
    return std::move(DynamicSprite({{1,172}},193,193));
} 
