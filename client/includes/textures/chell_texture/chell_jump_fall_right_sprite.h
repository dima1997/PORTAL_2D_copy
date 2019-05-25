#ifndef CHELL_JUMP_FALL_RIGHT_SPRITE_H
#define CHELL_JUMP_FALL_RIGHT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ChellJumpFallRightSprite : public DynamicSprite {
public:
    /*
    Inicializa un sprite dinamico de Chell cayendo
    hacia la derecha (tras haber saltado).
    Este sprite dinamico corresponde a una serie de sprites
    de la imagen ALL_CHELL_SPRITES_PART_1, de images_path.h.
    */
    ChellJumpFallRightSprite();

    /*
    Destruye el sprite dinamico de Chell cayendo 
    hacia la derecha (tras haber saltado).
    */
    virtual ~ChellJumpFallRightSprite();
};

#endif // CHELL_JUMP_FALL_RIGHT_SPRITE_H
