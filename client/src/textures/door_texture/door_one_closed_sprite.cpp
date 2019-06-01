#include "../../includes/door_texture/door_one_closed_sprite.h"

#include "../common_texture/dynamic_texture.h"

/*Incializa un sprite de puerta cerrada con numero 1.*/
DoorOneClosedSprite::DoorOneClosedSprite()
:   DynamicSprite(
        {1,21},
        193,385
    ) {}

/*Destruye el sprite de puerta cerrada con numero 1.*/
DoorOneClosedSprite::DoorOneClosedSprite() = default;
