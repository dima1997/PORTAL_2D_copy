#ifndef CHELL_DYING_SPRITE_H
#define CHELL_DYING_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ChellDyingSprite {
public:
    /*
    Devuelve un sprite dinamico de Chell muriendo.
    IMAGE_PATH : ALL_CHELL_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // CHELL_DYING_SPRITE_H
