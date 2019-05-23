#ifndef BLOCK_METAL_SPRITE_STRATEGY_H
#define BLOCK_METAL_SPRITE_STRATEGY_H

#include "../common_texture/sprite_strategy.h"

class BlockMetalSpriteStrategy : public SpriteStrategy {
public:
    /*
    Iniciliza un bloque sprite strategy, cuyos sprites 
    se encuentran en la imagen ALL_BLOCKS de 
    images_paths.h .
    */
    BlockMetalSpriteStrategy();

    /*Destruye uel sprite strategy del bloque de metal.*/
    virtual ~BlockMetalSpriteStrategy();    
};

#endif // BLOCK_METAL_SPRITE_STRATEGY_H
