#ifndef CHELL_JUMP_APEX_RIGHT_SPRITE_H
#define CHELL_JUMP_APEX_RIGHT_SPRITE_H

#include "../../common_texture/dynamic_sprite.h"

class ChellJumpApexRightSprite : public DynamicSprite {
public:
    /*
    Inicializa un sprite dinamico de Chell saltando 
    verticalemente (mirando hacia la derecha).
    Este sprite dinamico corresponde a una serie de sprites
    de la imagen ALL_CHELL_SPRITES_PART_1, de images_path.h.
    */
    ChellJumpApexRightSprite();

    /*
    Destruye el sprite dinamico de Chell saltando 
    verticalemente (mirando hacia la derecha).
    */
    virtual ~ChellJumpApexRightSprite();
};

#endif // CHELL_JUMP_APEX_RIGHT_SPRITE_H
