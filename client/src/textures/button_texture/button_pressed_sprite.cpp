#include "../../../includes/textures/button_texture/button_pressed_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

ButtonPressedSprite::ButtonPressedSprite() {}
ButtonPressedSprite::~ButtonPressedSprite() = default;

/*
Devuelve un sprite dinamico de boton presionado.
IMAGE_PATH : BUTTON_SPRITES
*/
DynamicSprite ButtonPressedSprite::get_sprite(){
    return std::move(DynamicSprite({{0,64}},174,54));
} 
