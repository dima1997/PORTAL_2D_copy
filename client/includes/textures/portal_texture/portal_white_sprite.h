#ifndef PORTAL_WHITE_SPRITE_H
#define PORTAL_WHITE_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class PortalWhiteSprite {
public:
    PortalWhiteSprite();
    virtual ~PortalWhiteSprite();
    
    /*
    Devuelve un sprite dinamico de portal blanco.
    IMAGE_PATH : PORTAL_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // PORTAL_WHITE_SPRITE_H
