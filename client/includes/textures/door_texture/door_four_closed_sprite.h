#ifndef DOOR_FOUR_CLOSED_SPRITE_H
#define DOOR_FOUR_CLOSED_SPRITE_H

#include "../common_texture/dynamic_texture.h"

class DoorFourClosedSprite : public DynamicSprite {
public:
    /*Inicializa un sprite de puerta cerrada con el numero 4.*/
    DoorFourClosedSprite();

    /*Destruye el sprite de puerta cerrada con el numero 4.*/
    virtual ~DoorFourClosedSprite();
};

#endif // DOOR_FOUR_CLOSED_SPRITE_H
