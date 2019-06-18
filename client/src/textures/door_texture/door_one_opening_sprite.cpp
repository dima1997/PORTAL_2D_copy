#include "../../../includes/textures/door_texture/door_one_opening_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

DoorOneOpeningSprite::DoorOneOpeningSprite() {}
DoorOneOpeningSprite::~DoorOneOpeningSprite() = default;

/*
Devuelve un sprite dinamico de puerta 1 abriendose.
IMAGE_PATH : DOORS_SPRITES
*/
DynamicSprite DoorOneOpeningSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {1,2051},
                {195,2051},
                {389,2051},
                {583,2051},
                {777,2051},
                {971,2051},
                {1165,2051},
                {1359,2051},
                {1553,2051},
                {1747,2051},
                {1,2437},
                {195,2437},
                {389,2437},
                {583,2437},
                {777,2437},
                {971,2437},
                {1165,2437},
                {1359,2437},
                {1553,2437}
            },
            193,385
        )
    );
} 
