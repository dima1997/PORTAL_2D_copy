#include "../../../includes/textures/energy_ball_texture/energy_ball_sprite_strategy.h"

#include "../../../includes/textures/energy_ball_texture/energy_ball_sprite.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"
#include "../../../includes/textures/common_texture/null_sprite.h"
#include <memory>

/*
Iniciliza una bola de energia sprite strategy, cuyos sprites 
se encuentran en la imagen ALL_ENERGY_BALLS_SPRTES de 
images_paths.h .
*/
EnergyBallSpriteStrategy::EnergyBallSpriteStrategy()
:   SpriteStrategy(
        EnergyBallSprite::get_sprite()    
    ), 
    spriteName(BALL_SHOW) {}

/*Destruye el sprite strategy de la bola de energia.*/
EnergyBallSpriteStrategy::~EnergyBallSpriteStrategy() = default;

/*Alterna entre mostrar o ocultar los sprites.*/
void EnergyBallSpriteStrategy::switch_sprite(){
    if (this->spriteName == BALL_SHOW){
        this->dynamicSprite = NullSprite::get_sprite();
        this->spriteName = BALL_HIDE;
    } else {
        this->dynamicSprite = EnergyBallSprite::get_sprite(); 
        this->spriteName = BALL_SHOW;
    }
}