#include "../../../includes/textures/door_texture/door_one_closed_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*Incializa un sprite de puerta cerrada con numero 1.*/
DoorOneClosedSprite::DoorOneClosedSprite()
:   DynamicSprite(
        {
            {1,21}
        },
        193,385
    ) {}

/*Destruye el sprite de puerta cerrada con numero 1.*/
DoorOneClosedSprite::~DoorOneClosedSprite() = default;

DynamicSprite DoorOneClosedSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {1,21}
            },
            193,385
        )
    );
} 
