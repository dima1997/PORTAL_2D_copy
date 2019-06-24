#ifndef LOADING_SPRITE_H
#define LOADING_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class LoadingSprite {
public:
    /*
    Devuelve un sprite dinamico partida cargando.
    IMAGE_PATH : LOADING_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // LOADING_SPRITE_H
