#ifndef RECEIVER_ON_SPRITE_H
#define RECEIVER_ON_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ReceiverOnSprite :  public DynamicSprite {
public:
    /*Inicializa un sprite de recibidor desbloqueado.*/
    ReceiverOnSprite();

    /*Destruye el sprite de recibidor desbloqueado.*/
    virtual ~ReceiverOnSprite();
    
};

#endif // RECEIVER_ON_SPRITE_H
