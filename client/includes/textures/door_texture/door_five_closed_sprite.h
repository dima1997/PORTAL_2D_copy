#ifndef DOOR_FIVE_CLOSED_SPRITE_H
#define DOOR_FIVE_CLOSED_SPRITE_H

#include "../common_texture/dynamic_texture.h"

class DoorFiveClosedSprite : public DynamicSprite {
public:
    /*Inicializa un sprite de puerta cerrada con el numero 5.*/
    DoorFiveClosedSprite();

    /*Destruye el sprite de puerta cerrada con el numero 5.*/
    virtual ~DoorFiveClosedSprite();
};

#endif // DOOR_FIVE_CLOSED_SPRITE_H
