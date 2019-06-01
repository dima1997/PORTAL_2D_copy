#include "../../../includes/textures/door_texture/door_five_closed_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*Incializa un sprite de puerta cerrada con numero 5.*/
DoorFiveClosedSprite::DoorFiveClosedSprite()
:   DynamicSprite(
        {
            {1,21}
        },
        193,385) {}

/*Destruye el sprite de puerta cerrada con numero 5.*/
DoorFiveClosedSprite::~DoorFiveClosedSprite() = default;
