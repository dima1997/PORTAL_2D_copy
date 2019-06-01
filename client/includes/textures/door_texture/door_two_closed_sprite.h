#ifndef DOOR_TWO_CLOSED_SPRITE_H
#define DOOR_TWO_CLOSED_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class DoorTwoClosedSprite : public DynamicSprite {
public:
    /*Inicializa un sprite de puerta cerrada con el numero 2.*/
    DoorTwoClosedSprite();

    /*Destruye el sprite de puerta cerrada con el numero 2.*/
    virtual ~DoorTwoClosedSprite();
};

#endif // DOOR_TWO_CLOSED_SPRITE_H
