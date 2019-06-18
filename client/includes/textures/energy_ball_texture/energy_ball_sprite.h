#ifndef ENERGY_BALL_SPRITE_H
#define ENERGY_BALL_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class EnergyBallSprite {
public:
    EnergyBallSprite();
    virtual ~EnergyBallSprite();
    
    /*
    Devuelve un sprite dinamico de bola de energia.
    IMAGE_PATH : ALL_ROCKS_AND_BALLS
    */
    static DynamicSprite get_sprite();  
};

#endif // ENERGY_BALL_SPRITE_H
