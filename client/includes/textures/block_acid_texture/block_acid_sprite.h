#ifndef BLOCK_ACID_SPRITE_H
#define BLOCK_ACID_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class BlockAcidSprite : public DynamicSprite {
public:
    /*Inicializa un sprite de bloque de acido estatico.*/
    BlockAcidSprite();

    /*Destruye el sprite de bloque de acido estatico.*/
    virtual ~BlockAcidSprite();

    static DynamicSprite get_sprite();
};

#endif // BLOCK_ACID_SPRITE_H
