#ifndef CHELL_JUMP_RISE_RIGHT_SPRITE_H
#define CHELL_JUMP_RISE_RIGHT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ChellJumpRiseRightSprite : public DynamicSprite {
public:
    /*
    Inicializa un sprite dinamico de Chell saltando 
    hacia la derecha.
    Este sprite dinamico corresponde a una serie de sprites
    de la imagen ALL_CHELL_SPRITES_PART_1, de images_path.h.
    */
    ChellJumpRiseRightSprite();

    /*
    Destruye el sprite dinamico de Chell saltando 
    hacia la derecha.
    */
    virtual ~ChellJumpRiseRightSprite();
};

#endif // CHELL_JUMP_RISE_RIGHT_SPRITE_H
