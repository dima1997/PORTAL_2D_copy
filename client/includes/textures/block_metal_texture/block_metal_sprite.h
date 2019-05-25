#ifndef BLOCK_METAL_SPRITE_H
#define BLOCK_METAL_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class BlockMetalSprite : public DynamicSprite {
public:
    /*Iniciliza un sprite de bloque de metal estatico.*/
    BlockMetalSprite();

    /*Destruye el sprite de bloque de metal estatico.*/
    virtual ~BlockMetalSprite();
};

#endif // BLOCK_METAL_SPRITE_H
