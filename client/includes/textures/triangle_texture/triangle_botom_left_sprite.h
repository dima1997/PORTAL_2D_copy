#ifndef TRIANGLE_BOTOM_LEFT_SPRITE_H
#define TRIANGLE_BOTOM_LEFT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class TriangleBotomLeftSprite : public DynamicSprite {
public:
    /*
    Iniciliza un sprite de triangulo de la esquina 
    inferior izquierda.
    */
    TriangleBotomLeftSprite();

    /*
    Destruye el sprite del triangulo de la esquina 
    inferior izquierda.
    */
    virtual ~TriangleBotomLeftSprite();
};

#endif // TRIANGLE_BOTOM_LEFT_SPRITE_H
