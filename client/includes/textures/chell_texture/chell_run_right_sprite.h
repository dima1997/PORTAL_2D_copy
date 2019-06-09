#ifndef CHELL_RUN_RIGHT_SPRITE_H
#define CHELL_RUN_RIGHT_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ChellRunRightSprite : public DynamicSprite {
public:
    /*
    Inicializa un sprite dinamico de Chell corriendo hacia
    la derecha.
    Este sprite dinamico corresponde a un series de sprites
    de la imagen ALL_CHELL_SPRITES, de images_path.h.
    */
    ChellRunRightSprite();

    /*
    Destruye el sprite dinamico de chell corriendo
    hacia la derecha.
    */
    virtual ~ChellRunRightSprite();

    static DynamicSprite get_sprite();
};

#endif // CHELL_RUN_RIGHT_SPRITE_H
