#ifndef CAKE_SPRITE_H
#define CAKE_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class CakeSprite {
public:
    CakeSprite();
    virtual ~CakeSprite();

    /*
    Devuelve un sprite dinamico de torta.
    IMAGE_PATH : CAKE_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // CAKE_SPRITE_H
