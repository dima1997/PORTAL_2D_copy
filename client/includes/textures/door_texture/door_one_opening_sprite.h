#ifndef DOOR_ONE_OPENING_SPRITE_H
#define DOOR_ONE_OPENING_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class DoorOneOpeningSprite {
public:
    DoorOneOpeningSprite();
    virtual ~DoorOneOpeningSprite();

    /*
    Devuelve un sprite dinamico de puerta uno abriendose.
    IMAGE_PATH : DOORS_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // DOOR_ONE_OPENING_SPRITE_H
