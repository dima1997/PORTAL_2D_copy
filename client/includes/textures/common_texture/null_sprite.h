#ifndef NULL_SPRITE_H
#define NULL_SPRITE_H

#include "dynamic_sprite.h"

class NullSprite {
public:
    NullSprite();
    virtual ~NullSprite();
    
    /*Develve un sprite dinamico nulo (sin imagen).*/
    static DynamicSprite get_sprite();    
};

#endif // NULL_SPRITE_H
