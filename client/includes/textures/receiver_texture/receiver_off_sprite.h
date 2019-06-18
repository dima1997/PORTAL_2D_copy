#ifndef RECEIVER_OFF_SPRITE_H
#define RECEIVER_OFF_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ReceiverOffSprite {
public:
    ReceiverOffSprite();
    virtual ~ReceiverOffSprite();

    /*
    Devuelve un sprite dinamico de receptor bloqueado.
    IMAGE_PATH : ALL_BLOCKS_SPRITES
    */
    static DynamicSprite get_sprite();
    
};

#endif // RECEIVER_OFF_SPRITE_H
