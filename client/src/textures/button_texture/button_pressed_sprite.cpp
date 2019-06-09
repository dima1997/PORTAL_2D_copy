#include "../../../includes/textures/button_texture/button_pressed_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Iniciliza un sprite de boton presionado que 
se encuentra en la imagen BUTTON_SPRITE en 
images_paths.h .
*/
ButtonPressedSprite::ButtonPressedSprite()
:   DynamicSprite(
        {
            {0,64}
        },
        174,54
    )
    {}
/*Destruye el sprite del boton presionado.*/
ButtonPressedSprite::~ButtonPressedSprite() = default;

DynamicSprite ButtonPressedSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {0,64}
            },
            174,54
        )
    );
} 
