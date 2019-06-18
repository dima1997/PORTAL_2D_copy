#ifndef ROCK_ONE_SPRITE_H
#define ROCK_ONE_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class RockOneSprite {
public:
    RockOneSprite();
    virtual ~RockOneSprite();

    /*
    Devuelve un sprite dinamico de roca 1.
    IMAGE_PATH : ALL_ROCKS_AND_BALLS
    */
    static DynamicSprite get_sprite();
};

#endif // ROCK_ONE_SPRITE_H
