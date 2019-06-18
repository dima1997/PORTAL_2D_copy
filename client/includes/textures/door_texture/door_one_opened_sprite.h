#ifndef DOOR_ONE_OPENED_SPRITE_H
#define DOOR_ONE_OPENED_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class DoorOneOpenedSprite {
public:
    DoorOneOpenedSprite();
    virtual ~DoorOneOpenedSprite();

    /*
    Devuelve un sprite dinamico de puerta 1 abierta.
    IMAGE_PATH : DOORS_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // DOOR_ONE_OPENED_SPRITE_H
