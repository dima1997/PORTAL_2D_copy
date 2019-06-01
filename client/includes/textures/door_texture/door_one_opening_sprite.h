#ifndef DOOR_ONE_OPENING_SPRITE_H
#define DOOR_ONE_OPENING_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class DoorOneOpeningSprite : public DynamicSprite {
public:
    /*Inicializa un sprite de puerta abriendose con el numero 1.*/
    DoorOneOpeningSprite();

    /*Destruye el sprite de puerta abriendose con el numero 1.*/
    virtual ~DoorOneOpeningSprite();
};

#endif // DOOR_ONE_OPENING_SPRITE_H
