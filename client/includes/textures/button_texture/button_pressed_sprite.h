#ifndef BUTTON_PRESSED_SPRITE_H
#define BUTTON_PRESSED_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ButtonPressedSprite : public DynamicSprite {
public:
    /*
    Iniciliza un sprite de boton presionado, correspondiente 
    a la imagen BUTTON_SPRITE de images_paths.h
    */
    ButtonPressedSprite();

    /*Destruye el sprite de boton presionado.*/
    virtual ~ButtonPressedSprite();
};

#endif // BUTTON_PRESSED_SPRITE_H
