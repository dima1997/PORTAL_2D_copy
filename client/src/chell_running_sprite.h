#ifndef CHELL_RUNNING_SPRITE_H
#define CHELL_RUNNING_SPRITE_H

#include "dynamic_sprite.h"

class ChellRunningSprite : public DynamicSprite {
public:
    /*
    Inicializa un sprite dinamico de Chell corriendo.
    Este sprite dinamico corresponde a un series de sprites
    de la imagen ALL_CHELL_SPRITES, de images_path.h.
    */
    ChellRunningSprite();

    /*Destruye el sprite dinamico de chell corriendo*/
    virtual ~ChellRunningSprite();
};

#endif // CHELL_RUNNING_SPRITE_H
