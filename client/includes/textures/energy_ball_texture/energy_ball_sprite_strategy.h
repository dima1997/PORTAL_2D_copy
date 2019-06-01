#ifndef ENERGY_BALL_SPRITE_STRATEGY_H
#define ENERGY_BALL_SPRITE_STRATEGY_H

#include "../common_texture/sprite_strategy.h"

enum EnergyBallSpriteName {
    BALL_SHOW,
    BALL_HIDE
};

class EnergyBallSpriteStrategy : public SpriteStrategy {
private: 
    EnergyBallSpriteName spriteName;
public:
    /*
    Iniciliza una bola de energia sprite strategy, 
    cuyos sprites se encuentran en la imagen 
    ALL_ENERGY_BALLS_SPRITES de images_paths.h .
    */
    EnergyBallSpriteStrategy();

    /*Destruye uel sprite strategy del portal.*/
    virtual ~EnergyBallSpriteStrategy();

    /*
    Alterna el sprite del portal entre visible 
    y no visible.
    */
    virtual void switch_sprite();
};

#endif // PORTAL_SPRITE_STRATEGY_H