#ifndef CHELL_JUMP_APEX_RIGHT_SPRITE_H
#define CHELL_JUMP_APEX_RIGHT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ChellJumpApexRightSprite {
public:
    ChellJumpApexRightSprite();
    virtual ~ChellJumpApexRightSprite();

    /*
    Devuelve un sprite dinamico de Chell saltando
    verticalmente.
    */
    static DynamicSprite get_sprite();
};

#endif // CHELL_JUMP_APEX_RIGHT_SPRITE_H
