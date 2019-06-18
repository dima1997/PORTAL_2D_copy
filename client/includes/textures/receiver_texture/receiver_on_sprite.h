#ifndef RECEIVER_ON_SPRITE_H
#define RECEIVER_ON_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ReceiverOnSprite {
public:
    ReceiverOnSprite();
    virtual ~ReceiverOnSprite();
    
    /*
    Devuelve un sprite dinamico de receptor desbloqueado.
    IMAGE_PATH : ALL_BLOCKS_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // RECEIVER_ON_SPRITE_H
