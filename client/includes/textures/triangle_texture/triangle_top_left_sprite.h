#ifndef TRIANGLE_TOP_LEFT_SPRITE_H
#define TRIANGLE_TOP_LEFT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class TriangleTopLeftSprite : public DynamicSprite {
public:
    /*
    Iniciliza un sprite de triangulo de la esquina 
    superior izquierda.
    */
    TriangleTopLeftSprite();

    /*
    Destruye el sprite del triangulo de la esquina 
    superior izquierda.
    */
    virtual ~TriangleTopLeftSprite();

    static DynamicSprite get_sprite();
};

#endif // V
