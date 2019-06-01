#include "../../../includes/textures/energy_ball_texture/energy_ball_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Iniciliza un sprite de bola de energia que se 
encuentra en la imagen ALL_ENERGY_BALLS_SPRITE .
*/
EnergyBallSprite::EnergyBallSprite()
:   DynamicSprite(
        {
            {1,824},
            {253,824},
            {505,824},
            {757,824},
        },
        251,252
    )
    {}
/*Destruye el sprite de la bola de energia.*/
EnergyBallSprite::~EnergyBallSprite() = default;