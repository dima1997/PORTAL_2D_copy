#ifndef CHELL_SWEAT_SPRITE_H
#define CHELL_SWEAT_SPRITE_H

#include "dynamic_sprite.h"

class ChellSweatSprite : public DynamicSprite {
public:
    /*
    Inicializa un sprite dinamico de Chell sudando.
    Este sprite dinamico corresponde a un series de sprites
    de la imagen ALL_CHELL_SPRITES, de images_path.h.
    */
    ChellSweatSprite();

    /*Destruye el sprite dinamico de chell sudando*/
    virtual ~ChellSweatSprite();
};

#endif // CHELL_SWEAT_SPRITE_H