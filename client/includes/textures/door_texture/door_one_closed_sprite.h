#ifndef DOOR_ONE_CLOSED_SPRITE_H
#define DOOR_ONE_CLOSED_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class DoorOneClosedSprite : public DynamicSprite {
public:
    /*Inicializa un sprite de puerta cerrada con el numero 1.*/
    DoorOneClosedSprite();

    /*Destruye el sprite de puerta cerrada con el numero 1.*/
    virtual ~DoorOneClosedSprite();

    static DynamicSprite get_sprite();
};

#endif // DOOR_ONE_CLOSED_SPRITE_H
