#ifndef CHELL_DEAD_STRATEGY_H
#define CHELL_DEAD_STRATEGY_H

#include "../common_texture/sprite_strategy.h"
#include "../common_texture/area.h"

enum ChellDeadSpriteName {
    DYING,
    DEAD
};

class ChellDeadStrategy : public SpriteStrategy {
private: 
    ChellDeadSpriteName spriteName;

public:
    /*Inicializa el estado de sprite de Chell muerta.*/
    ChellDeadStrategy();

    /*Destruye el estado de sprite de Chell muerta*/
    virtual ~ChellDeadStrategy();

    /*
    Devuelve el area correspondiente al siguiente sprite 
    de Chell muerta, en la imagen ALL_CHELL_SPRITES de 
    images_path.h .
    */
    virtual Area getNextArea() override;  
};

#endif // CHELL_DEAD_STRATEGY_H
