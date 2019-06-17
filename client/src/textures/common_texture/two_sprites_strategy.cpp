#include "../../../includes/textures/common_texture/two_sprites_strategy.h"

#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"
#include "../../../includes/textures/common_texture/area.h"

/*
PRE: Recibe dos sprites (DynamicSprite).
POST: Inicializa un strategy que puede 
altenar entre estos dos sprites.
*/
TwoSpritesStrategy::TwoSpritesStrategy(
    DynamicSprite firstSprite,
    DynamicSprite secondSprite
)
:   SpriteStrategy(firstSprite),
    secondSprite(secondSprite)
{}

/*Destruye el strategy.*/
TwoSpritesStrategy:: ~TwoSpritesStrategy() = default;

/*Alterna entre uno y otro sprite.*/
void TwoSpritesStrategy::switch_sprite(){
    DynamicSprite auxSprite = this->dynamicSprite;
    this->dynamicSprite = this->secondSprite;
    this->secondSprite = auxSprite;
}
