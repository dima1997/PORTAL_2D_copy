#include "../../../includes/textures/door_texture/door_one_closed_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

DoorOneClosedSprite::DoorOneClosedSprite() {}
DoorOneClosedSprite::~DoorOneClosedSprite() = default;

/*
Devuelve un sprite dinamico de puerta cerrada.
IMAGE_PATH : DOORS_SPRITES
*/
DynamicSprite DoorOneClosedSprite::get_sprite(){
    return DynamicSprite({{1,21}},193,385);
} 
