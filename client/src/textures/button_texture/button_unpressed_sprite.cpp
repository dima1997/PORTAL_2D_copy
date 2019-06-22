#include "../../../includes/textures/button_texture/button_unpressed_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

ButtonUnPressedSprite::ButtonUnPressedSprite() {}
ButtonUnPressedSprite::~ButtonUnPressedSprite() = default;

/*
Devuelve un sprite dinamico de un boton sin presionar
IMAGE_PATH : BUTTON_SPRITES
*/
DynamicSprite ButtonUnPressedSprite::get_sprite(){
    return DynamicSprite({{0,0},},174,54);
} 
