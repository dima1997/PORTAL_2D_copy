#ifndef BACKGROUND_ONE_SPRITE_H
#define BACKGROUND_ONE_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class BackgroundOneSprite {
public:
    BackgroundOneSprite();
    virtual ~BackgroundOneSprite();

    /*
    Devuelve un sprite dinamico de 
    fondo de pantalla 1.
    IMAGE_PATH : BACKGROUND_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // BACKGROUND_ONE_SPRITE_H
