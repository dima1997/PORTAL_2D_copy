#ifndef CHELL_SWEAT_RIGHT_SPRITE_H
#define CHELL_SWEAT_RIGHT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ChellSweatRightSprite{
public:
    /*
    Inicializa un sprite dinamico de Chell sudando 
    (sentido hacia derecha).
    Este sprite dinamico corresponde a una serie de sprites
    de la imagen ALL_CHELL_SPRITES, de images_path.h.
    */
    ChellSweatRightSprite();

    /*Destruye el sprite dinamico de chell sudando*/
    virtual ~ChellSweatRightSprite();

    static DynamicSprite get_sprite();
};

#endif // CHELL_SWEAT_RIGHT_SPRITE_H
