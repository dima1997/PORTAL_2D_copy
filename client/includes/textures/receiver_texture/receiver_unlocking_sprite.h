#ifndef RECEIVER_UNLOCKIN_SPRITE_H
#define RECEIVER_UNLOCKIN_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ReceiverUnlockingSprite {
public:
    ReceiverUnlockingSprite();
    virtual ~ReceiverUnlockingSprite();

    /*
    Devuelve un sprite dinamico de receptor desbloqueandose.
    IMAGE_PATH : ALL_BLOCKS_SPRITES 
    */
    static DynamicSprite get_sprite();
};

#endif // RECEIVER_UNLOCKIN_SPRITE_H
