#ifndef TRIANGLE_BOTOM_RIGHT_SPRITE_H
#define TRIANGLE_BOTOM_RIGHT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class TriangleBotomRightSprite : public DynamicSprite {
public:
    /*
    Iniciliza un sprite de triangulo de la esquina 
    inferior derecha.
    */
    TriangleBotomRightSprite();

    /*
    Destruye el sprite del triangulo de la esquina 
    inferior derecha.
    */
    virtual ~TriangleBotomRightSprite();
};

#endif // TRIANGLE_BOTOM_RIGHT_SPRITE_H
