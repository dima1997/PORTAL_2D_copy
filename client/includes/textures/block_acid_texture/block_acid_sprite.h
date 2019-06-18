#ifndef BLOCK_ACID_SPRITE_H
#define BLOCK_ACID_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class BlockAcidSprite {
public:
    BlockAcidSprite();
    virtual ~BlockAcidSprite();

    /*
    Devuelve un sprite dinamico de bloque de acido.
    IMAGE_PATH : ALL_BLOCKS_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // BLOCK_ACID_SPRITE_H
