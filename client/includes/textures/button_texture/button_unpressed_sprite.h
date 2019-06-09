#ifndef BUTTON_UNPRESSED_SPRITE_H
#define BUTTON_UNPRESSED_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class ButtonUnPressedSprite : public DynamicSprite {
public:
    /*
    Iniciliza un sprite de boton sin presionar, correspondiente 
    a la imagen BUTTON_SPRITE de images_paths.h
    */
    ButtonUnPressedSprite();

    /*Destruye el sprite de boton sin presionar.*/
    virtual ~ButtonUnPressedSprite();

    static DynamicSprite get_sprite();
};

#endif // BUTTON_UNPRESSED_SPRITE_H
