#ifndef TRIANGLE_BOTOM_LEFT_SPRITE_H
#define TRIANGLE_BOTOM_LEFT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class TriangleBotomLeftSprite {
public:
    TriangleBotomLeftSprite();
    virtual ~TriangleBotomLeftSprite();

    /*
    Devuelve un sprite dinamico de triangulo rectangulo 
    en la esquina inferior izquierda.
    IMAGE_PATH : ALL_TRIANGLES_SPRITES 
    */
    static DynamicSprite get_sprite();
};

#endif // TRIANGLE_BOTOM_LEFT_SPRITE_H
