#include "../../../includes/textures/door_texture/door_one_opened_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

DoorOneOpenedSprite::DoorOneOpenedSprite() {}
DoorOneOpenedSprite::~DoorOneOpenedSprite() = default;

/*
Devuelve un sprite dinamico de la puerta 1 abriendose.
IMAGE_PATH : DOORS_SPRITES
*/
DynamicSprite DoorOneOpenedSprite::get_sprite(){
    return DynamicSprite({{1553,2437}},193,385);
} 
