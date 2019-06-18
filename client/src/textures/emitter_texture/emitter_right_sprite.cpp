#include "../../../includes/textures/emitter_texture/emitter_right_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

EmitterRightSprite::EmitterRightSprite() {}
EmitterRightSprite::~EmitterRightSprite() = default;

/*
Devuelve un sprite dinamico de emisor hacia derecha.
IMAGE_PATH : ALL_BLOCKS_SPRITES
*/
DynamicSprite EmitterRightSprite::get_sprite(){
    return std::move(DynamicSprite({{1,1028}},193,193));
} 