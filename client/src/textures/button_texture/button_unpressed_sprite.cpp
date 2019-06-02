#include "../../../includes/textures/button_texture/button_unpressed_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Iniciliza un sprite de boton sin presionar que 
se encuentra en la imagen BUTTON_SPRITE en 
images_paths.h .
*/
ButtonUnPressedSprite::ButtonUnPressedSprite()
:   DynamicSprite(
        {
            {0,0},
        },
        174,54
    )
    {}
/*Destruye el sprite del boton sin presionar.*/
ButtonUnPressedSprite::~ButtonUnPressedSprite() = default;
