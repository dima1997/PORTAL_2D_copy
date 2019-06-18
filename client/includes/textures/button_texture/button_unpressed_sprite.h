#ifndef BUTTON_UNPRESSED_SPRITE_H
#define BUTTON_UNPRESSED_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ButtonUnPressedSprite {
public:
    ButtonUnPressedSprite();
    virtual ~ButtonUnPressedSprite();

    /*
    Devuelve un sprite dinamico de un boton sin presionar
    IMAGE_PATH : BUTTON_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // BUTTON_UNPRESSED_SPRITE_H
