#ifndef DOOR_ONE_CLOSED_SPRITE_H
#define DOOR_ONE_CLOSED_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class DoorOneClosedSprite {
public:
    DoorOneClosedSprite();
    virtual ~DoorOneClosedSprite();

    /*
    Devuelve un sprite dinamico de puerta 1 cerrada.
    IMAGE_PATH : DOORS_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // DOOR_ONE_CLOSED_SPRITE_H
