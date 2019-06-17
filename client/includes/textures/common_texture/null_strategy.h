#ifndef TWO_SPRITES_STRATEGY_H
#define TWO_SPRITES_STRATEGY_H

#include "sprite_strategy.h"
#include "dynamic_sprite.h"

class TwoSpriteStrategy : public SpriteStrategy {
private:
    DynamicSprite mainSprite;
    DynamicSprite nullSprite;
public:
    /*
    PRE: 
    POST: Inicializa un sprite strategy de dos sprites.
    */
    TwoSpriteStrategy(DynamicSprite mainSprite);

    /*Destruye el strategy.*/
    virtual ~TwoSpriteStrategy();

    /*Alterna entre uno y otro sprite.*/
    virtual switch_sprite(){

    }  
};

#endif // TWO_SPRITES_STRATEGY_H
