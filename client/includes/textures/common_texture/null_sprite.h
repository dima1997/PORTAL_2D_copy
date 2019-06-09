#ifndef NULL_SPRITE_H
#define NULL_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class NullSprite :  public DynamicSprite {
public:
    /*Iniciliza un sprite nulo (sin imagen).*/
    NullSprite();

    /*Destruye el sprite nulo.*/
    virtual ~NullSprite();
    
    static DynamicSprite get_sprite();    
};

#endif // NULL_SPRITE_H
