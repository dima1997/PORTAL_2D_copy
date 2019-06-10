#ifndef CHELL_STAND_RIGHT_SPRITE_H
#define CHELL_STAND_RIGHT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ChellStandRightSprite {
public:
    /*
    Devuelve un sprite dinamico de Chell parada
    (mirando hacia la derecha).
    Este sprite dinamico corresponde a una serie de 
    sprites de la imagen ALL_CHELL_SPRITES, de 
    images_path.h.
    */
    static DynamicSprite get_sprite();
};

#endif // CHELL_STAND_RIGHT_SPRITE_H
