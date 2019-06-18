#ifndef BLOCK_METAL_SPRITE_H
#define BLOCK_METAL_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class BlockMetalSprite {
public:
    BlockMetalSprite();
    virtual ~BlockMetalSprite();

    /*
    Devuelve un sprite dinamico de bloque de metal.
    IMAGE_PATH : ALL_BLOCKS_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // BLOCK_METAL_SPRITE_H
