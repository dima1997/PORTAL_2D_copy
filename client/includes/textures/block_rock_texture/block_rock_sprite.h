#ifndef BLOCK_ROCK_SPRITE_H
#define BLOCK_ROCK_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class BlockRockSprite : public DynamicSprite {
public:
    /*Iniciliza un sprite de bloque de piedra estatico.*/
    BlockRockSprite();

    /*Destruye el sprite de bloque de piedra estatico.*/
    virtual ~BlockRockSprite();
};

#endif // BLOCK_ROCK_SPRITE_H
