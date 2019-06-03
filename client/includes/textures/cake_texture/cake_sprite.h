#ifndef CAKE_SPRITE_H
#define CAKE_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class CakeSprite : public DynamicSprite {
public:
    /*Iniciliza un sprite de bloque de torta.*/
    CakeSprite();

    /*Destruye el sprite de bloque de torta.*/
    virtual ~CakeSprite();
};

#endif // CAKE_SPRITE_H
