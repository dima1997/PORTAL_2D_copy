#ifndef EMITTER_RIGHT_SPRITE_H
#define EMITTER_RIGHT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class EmitterRightSprite {
public:
    EmitterRightSprite();
    virtual ~EmitterRightSprite();

    /*
    Devuelve un sprite dinamico de emisor hacia derecha.
    IMAGE_PATH : ALL_BLOCKS_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // EMITTER_RIGHT_SPRITE_H
