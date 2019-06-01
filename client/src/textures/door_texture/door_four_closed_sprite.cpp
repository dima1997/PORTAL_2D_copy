#include "../../../includes/textures/door_texture/door_four_closed_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*Incializa un sprite de puerta cerrada con numero 4.*/
DoorFourClosedSprite::DoorFourClosedSprite()
:   DynamicSprite(
        {
            {1,1239}
        },
        193,385
    ) {}

/*Destruye el sprite de puerta cerrada con numero 4.*/
DoorFourClosedSprite::~DoorFourClosedSprite() = default;
