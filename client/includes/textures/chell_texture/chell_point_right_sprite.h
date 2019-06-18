#ifndef CHELL_POINT_RIGHT_SPRITE_H
#define CHELL_POINT_RIGHT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ChellPointRightSprite {
public:
    ChellPointRightSprite();
    virtual ~ChellPointRightSprite();

    /*Devuelve sprite de Chell apuntando a derecha.*/
    static DynamicSprite point_right();

    /*Devuelve sprite de Chell apuntando ariba.*/
    static DynamicSprite point_up();

    /*Devuelve sprite de Chell apuntando arriba y a derecha.*/
    static DynamicSprite point_right_up();

    /*Devuelve sprite de Chell apuntando abajo.*/
    static DynamicSprite point_down();

    /*Devuelve sprite de Chell apuntando abajo y a derecha.*/
    static DynamicSprite point_right_down();
    
};

#endif // CHELL_POINT_RIGHT_SPRITE_H
