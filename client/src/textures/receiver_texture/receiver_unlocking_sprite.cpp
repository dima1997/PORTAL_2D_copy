#include "../../../includes/textures/receiver_texture/receiver_unlocking_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

ReceiverUnlockingSprite::ReceiverUnlockingSprite() {}
ReceiverUnlockingSprite::~ReceiverUnlockingSprite() = default;

/*
Devuelve un sprite dinamico de receptor desbloqueandose.
IMAGE_PATH : ALL_BLOCKS_SPRITES 
*/
DynamicSprite ReceiverUnlockingSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {202,2538},
                {403,2538},
                {604,2538},
                {805,2538}
            },
            200,197
        )
    );
}