#ifndef BARRIER_SPRITE_H
#define BARRIER_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class BarrierSprite : public DynamicSprite {
public:
    /*Inicializa un sprite de barrera.*/
    BarrierSprite();

    /*Destruye el sprite de barrera.*/
    virtual ~BarrierSprite();
};

#endif // BARRIER_SPRITE_H
