#ifndef RECEIVER_OFF_SPRITE_H
#define RECEIVER_OFF_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ReceiverOffSprite :  public DynamicSprite {
public:
    /*Iniciliza un sprite de recibidor bloqueado.*/
    ReceiverOffSprite();

    /*Destruye el sprite de recibidor bloqueado.*/
    virtual ~ReceiverOffSprite();

    static DynamicSprite get_sprite();
    
};

#endif // RECEIVER_OFF_SPRITE_H
