#ifndef TRIANGLE_TOP_RIGHT_SPRITE_H
#define TRIANGLE_TOP_RIGHT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class TriangleTopRightSprite : public DynamicSprite {
public:
    /*
    Iniciliza un sprite de triangulo de la esquina 
    superior derecha.
    */
    TriangleTopRightSprite();

    /*
    Destruye el sprite del triangulo de la esquina 
    superior derecha.
    */
    virtual ~TriangleTopRightSprite();

    static DynamicSprite get_sprite();
};

#endif // TRIANGLE_TOP_RIGHT_SPRITE_H
