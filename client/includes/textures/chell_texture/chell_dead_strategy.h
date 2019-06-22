#ifndef CHELL_DEAD_STRATEGY_H
#define CHELL_DEAD_STRATEGY_H

#include "../common_texture/sprite_strategy.h"
#include "../common_texture/area.h"

enum ChellDeadSpriteName {
    CHELL_SPRITE_DYING,
    CHELL_SPRITE_DEAD
};

class ChellDeadStrategy : public SpriteStrategy {
private: 
    ChellDeadSpriteName spriteName;

public:
    /*Inicializa el estado de sprite de Chell muerta.*/
    ChellDeadStrategy();

    /*Destruye el estado de sprite de Chell muerta*/
    virtual ~ChellDeadStrategy();

    /*Actualiza el sprite al siguiente a usar.*/
    virtual void update();  
};

#endif // CHELL_DEAD_STRATEGY_H
