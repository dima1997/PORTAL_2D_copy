#ifndef BLOCK_ROCK_SPRITE_H
#define BLOCK_ROCK_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class BlockRockSprite {
public:
    BlockRockSprite();
    virtual ~BlockRockSprite();

    /*
    Devuelve un sprite dinamico de bloque de roca.
    IMAGE_PATH : ALL_BLOCKS_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // BLOCK_ROCK_SPRITE_H
