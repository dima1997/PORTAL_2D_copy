#ifndef ROCK_SPRITE_H
#define ROCK_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class RockSprite {
public:
    RockSprite();
    virtual ~RockSprite();
    /*
    Devuelve un sprite dinamico de roca 1.
    IMAGE_PATH : ALL_ROCKS_AND_BALLS
    */
    static DynamicSprite rock_one();

    /*
    Devuelve un sprite dinamico de roca 2.
    IMAGE_PATH : ALL_ROCKS_AND_BALLS
    */
    static DynamicSprite rock_two();

    /*
    Devuelve un sprite dinamico de roca 3.
    IMAGE_PATH : ALL_ROCKS_AND_BALLS
    */
    static DynamicSprite rock_three();

    /*
    Devuelve un sprite dinamico de roca 4.
    IMAGE_PATH : ALL_ROCKS_AND_BALLS
    */
    static DynamicSprite rock_four();

    /*
    Devuelve un sprite dinamico de roca 5.
    IMAGE_PATH : ALL_ROCKS_AND_BALLS
    */
    static DynamicSprite rock_five();

    /*
    Devuelve un sprite dinamico de roca 6.
    IMAGE_PATH : ALL_ROCKS_AND_BALLS
    */
    static DynamicSprite rock_six();

    /*
    Devuelve un sprite dinamico de roca 7.
    IMAGE_PATH : ALL_ROCKS_AND_BALLS
    */
    static DynamicSprite rock_seven();

    /*
    Devuelve un sprite dinamico de roca 8.
    IMAGE_PATH : ALL_ROCKS_AND_BALLS
    */
    static DynamicSprite rock_eight();
};

#endif // ROCK_SPRITE_H
