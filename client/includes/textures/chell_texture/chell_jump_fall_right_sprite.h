#ifndef CHELL_JUMP_FALL_RIGHT_SPRITE_H
#define CHELL_JUMP_FALL_RIGHT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ChellJumpFallRightSprite {
public:
    ChellJumpFallRightSprite();
    virtual ~ChellJumpFallRightSprite();

    /*
    Devuelve un sprite dinamico de chell 
    cayendo hacia la derecha.
    */
    static DynamicSprite get_sprite();
};

#endif // CHELL_JUMP_FALL_RIGHT_SPRITE_H
