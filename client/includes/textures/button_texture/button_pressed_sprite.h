#ifndef BUTTON_PRESSED_SPRITE_H
#define BUTTON_PRESSED_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ButtonPressedSprite {
public:
    ButtonPressedSprite();
    virtual ~ButtonPressedSprite();

    /*
    Devuelve un sprite dinamico de boton presionado.
    IMAGE_PATH : BUTTON_SPRITES
    */
    static DynamicSprite get_sprite();
};

#endif // BUTTON_PRESSED_SPRITE_H
