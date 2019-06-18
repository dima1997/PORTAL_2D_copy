#include "../../../includes/textures/receiver_texture/receiver_off_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

ReceiverOffSprite::ReceiverOffSprite() {}
ReceiverOffSprite::~ReceiverOffSprite() = default;

/*
Devuelve un sprite dinamico de receptor bloqueado.
IMAGE_PATH : ALL_BLOCKS_SPRITES
*/
DynamicSprite ReceiverOffSprite::get_sprite(){
    return std::move(DynamicSprite({{1,2538}},200,197));
} 