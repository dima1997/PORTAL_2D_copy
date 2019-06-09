#ifndef RECEIVER_UNLOCKIN_SPRITE_H
#define RECEIVER_UNLOCKIN_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ReceiverUnlockingSprite :  public DynamicSprite {
public:
    /*Inicializa un sprite recibidor desbloqueandose.*/
    ReceiverUnlockingSprite();

    /*Destruye el sprite de recibidor desbloqueandose.*/
    virtual ~ReceiverUnlockingSprite();

    static DynamicSprite get_sprite();
};

#endif // RECEIVER_UNLOCKIN_SPRITE_H
