#ifndef RECEIVER_SPRITE_STRATEGY_H
#define RECEIVER_SPRITE_STRATEGY_H

#include "../common_texture/sprite_strategy.h"

enum ReceiverSpriteName {
    RECEIVER_ON,
    RECEIVER_OFF,
    RECEIVER_UNLOCKING
};

class ReceiverSpriteStrategy : public SpriteStrategy {
private: 
    ReceiverSpriteName spriteName;
public:
    /*
    Inicializa un recibidor sprite strategy, cuyos sprites 
    se encuentran en la imagen ALL_BLOCKS_SPRITES de 
    images_paths.h .
    */
    ReceiverSpriteStrategy();

    /*Destruye uel sprite strategy del portal.*/
    virtual ~ReceiverSpriteStrategy();

    /*
    Alterna entre recibidor bloqueado y desbloqueado.
    */
    virtual void switch_sprite();

    /*Actualiza el sprite al siguiente a ser usado.*/
    virtual void update();
};

#endif // RECEIVER_SPRITE_STRATEGY_H
