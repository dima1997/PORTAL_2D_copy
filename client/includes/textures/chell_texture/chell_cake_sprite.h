#ifndef CHELL_CAKE_SPRITE_H
#define CHELL_CAKE_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ChellCakeSprite {
public:
    /*
    Devuelve un sprite dinamico de Chell comiendose 
    la torta.
    Este sprite dinamico corresponde a una serie de 
    sprites de la imagen ALL_CHELL_SPRITES, de 
    images_path.h.
    */
    static DynamicSprite get_sprite();
};

#endif // CHELL_CAKE_SPRITE_H
