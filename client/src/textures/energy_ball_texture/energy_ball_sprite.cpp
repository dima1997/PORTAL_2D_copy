#include "../../../includes/textures/energy_ball_texture/energy_ball_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

EnergyBallSprite::EnergyBallSprite() {}
EnergyBallSprite::~EnergyBallSprite() = default;

/*
Devuelve un sprite dinamico de bola de energia.
IMAGE_PATH : ALL_ROCKS_AND_BALLS
*/
DynamicSprite EnergyBallSprite::get_sprite(){
    return DynamicSprite(
        {
            {1,15},
            {253,15},
            {505,15},
            {757,15},
        },
        251,252
    );
} 