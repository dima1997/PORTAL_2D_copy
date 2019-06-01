#include "../../../includes/textures/door_texture/door_two_closed_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"
/*Incializa un sprite de puerta cerrada con numero 2.*/
DoorTwoClosedSprite::DoorTwoClosedSprite()
:   DynamicSprite(
        {
            {1,427}
        },
        193,385
    ) {}

/*Destruye el sprite de puerta cerrada con numero 2.*/
DoorTwoClosedSprite::~DoorTwoClosedSprite() = default;

