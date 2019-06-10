#include "../../../includes/textures/door_texture/door_one_opened_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*Inicializa un sprite de puerta abierta con el numero 1.*/
DoorOneOpenedSprite::DoorOneOpenedSprite()
:   DynamicSprite(DoorOneOpenedSprite::get_sprite()) {}

/*Destruye el sprite de puerta abierta con el numero 1.*/
DoorOneOpenedSprite::~DoorOneOpenedSprite() = default;

DynamicSprite DoorOneOpenedSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {1553,2437}
            },
            193,385
        )
    );
} 
