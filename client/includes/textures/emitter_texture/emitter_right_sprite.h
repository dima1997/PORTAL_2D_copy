#ifndef EMITTER_RIGHT_SPRITE_H
#define EMITTER_RIGHT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class EmitterRightSprite : public DynamicSprite {
public:
    /*Iniciliza un sprite de bloque emisor a derecha.*/
    EmitterRightSprite();

    /*Destruye el sprite de bloque emisor a derecha.*/
    virtual ~EmitterRightSprite();
};

#endif // EMITTER_RIGHT_SPRITE_H
