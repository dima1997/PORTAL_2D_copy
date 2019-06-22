#ifndef NULL_STRATEGY_H
#define NULL_STRATEGY_H

#include "two_sprites_strategy.h"
#include "dynamic_sprite.h"

enum NullEndSpriteName {
    NULL_SPRITE,
    NOT_NULL_SPRITE
};

class NullEndStrategy : public TwoSpritesStrategy {
private:
    NullEndSpriteName spriteName;
public:
    /*
    PRE: Recibe recibe el sprite dinamico a usar antes de 
    pasar a sprite nulo
    Inicializa un sprite strategy de dos sprites.
    */
    NullEndStrategy(const DynamicSprite & mainSprite);

    /*Destruye el strategy.*/
    virtual ~NullEndStrategy();

    /*Actualiza el sprite al siguiente a usar.*/
    virtual void update();
};

#endif // NULL_STRATEGY_H
