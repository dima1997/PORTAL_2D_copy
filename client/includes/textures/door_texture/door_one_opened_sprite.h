#ifndef DOOR_ONE_OPENED_SPRITE_H
#define DOOR_ONE_OPENED_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class DoorOneOpenedSprite : public DynamicSprite {
public:
    /*Inicializa un sprite de puerta abierta con el numero 1.*/
    DoorOneOpenedSprite();

    /*Destruye el sprite de puerta abierta con el numero 1.*/
    virtual ~DoorOneOpenedSprite();

    static DynamicSprite get_sprite();
};

#endif // DOOR_ONE_OPENED_SPRITE_H
