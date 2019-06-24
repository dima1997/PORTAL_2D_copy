#ifndef TWO_SPRITES_STRATEGY_H
#define TWO_SPRITES_STRATEGY_H

#include "sprite_strategy.h"
#include "dynamic_sprite.h"

class TwoSpritesStrategy : public SpriteStrategy {
private:
    // El primero es el de la clase padre
    DynamicSprite secondSprite;
public:
    /*
    PRE: 
    POST: Inicializa un sprite strategy de dos sprites.
    */
    TwoSpritesStrategy(
        DynamicSprite firstSprite,
        DynamicSprite secondSprite
    );

    /*Destruye el strategy.*/
    virtual ~TwoSpritesStrategy();

    /*Alterna entre uno y otro sprite.*/
    virtual void switch_sprite();
};

#endif // TWO_SPRITES_STRATEGY_H
