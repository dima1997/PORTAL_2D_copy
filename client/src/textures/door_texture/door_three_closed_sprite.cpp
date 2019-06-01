#include "../../../includes/textures/door_texture/door_three_closed_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*Incializa un sprite de puerta cerrada con numero 3.*/
DoorThreeClosedSprite::DoorThreeClosedSprite()
:   DynamicSprite(
        {
            {1,833}
        },
        193,385
    ) {}

/*Destruye el sprite de puerta cerrada con numero 3.*/
DoorThreeClosedSprite::~DoorThreeClosedSprite() = default;
