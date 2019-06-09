#ifndef PORTAL_BLUE_SPRITE_H
#define PORTAL_BLUE_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class PortalBlueSprite :  public DynamicSprite {
public:
    /*Iniciliza un sprite de portal azul.*/
    PortalBlueSprite();

    /*Destruye el sprite de portal azul.*/
    virtual ~PortalBlueSprite();
    
    static DynamicSprite get_sprite();
};

#endif // PORTAL_BLUE_SPRITE_H
