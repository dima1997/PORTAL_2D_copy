#include "../../../includes/textures/receiver_texture/receiver_on_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

ReceiverOnSprite::ReceiverOnSprite() {}
ReceiverOnSprite::~ReceiverOnSprite() = default;

/*
Devuelve un sprite dinamico de receptor desbloqueado.
IMAGE_PATH : ALL_BLOCKS_SPRITES
*/
DynamicSprite ReceiverOnSprite::get_sprite(){
    return std::move(DynamicSprite({{1006,2538}},200,197));
} 