#ifndef BARRIER_SPRITE_H
#define BARRIER_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class BarrierSprite {
public:
    BarrierSprite();
    virtual ~BarrierSprite();

    /*
    Devuelve un sprite dinamico de 
    barrera de energia.
    IMAGE_PATH : BARRIER_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // BARRIER_SPRITE_H
