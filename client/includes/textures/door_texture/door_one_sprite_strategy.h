#ifndef DOOR_ONE_SPRITE_STRATEGY_H
#define DOOR_ONE_SPRITE_STRATEGY_H

#include "../common_texture/sprite_strategy.h"
#include "../common_texture/area.h"

enum DoorSpriteName {
    DOOR_OPEN,
    DOOR_OPENING,
    DOOR_CLOSING,
    DOOR_CLOSE
};

class DoorOneSpriteStrategy : public SpriteStrategy {
private:
    DoorSpriteName spriteName;
public:
    /*Inicializa el manejador de sprites de la puerta.*/
    DoorOneSpriteStrategy();

    /*Destruye el manejador de sprites de la puerta.*/
    virtual ~DoorOneSpriteStrategy();

    /*Alterna entre puerta abierta y cerrada.*/
    virtual void switch_sprite() ;

    /*Actualiza el estado de la puerta.*/
    virtual void update();
};

#endif // DOOR_ONE_SPRITE_STRATEGY_H
