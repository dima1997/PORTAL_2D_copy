#include "../../../includes/textures/button_texture/button_sprite_strategy.h"

#include "../../../includes/textures/button_texture/button_unpressed_sprite.h"
#include "../../../includes/textures/button_texture/button_pressed_sprite.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"
#include "../../../includes/textures/common_texture/null_sprite.h"

#include <memory>

/*
Iniciliza un boton sprite strategy, cuyos 
sprites se encuentra en la imagen BUTTON_SPRITE 
en images_paths.h .
*/
ButtonSpriteStrategy::ButtonSpriteStrategy() 
:   SpriteStrategy(
        ButtonUnPressedSprite::get_sprite()    
    ), 
    spriteName(BUTTON_NOT_PRESSED) {}

/*Destruye el sprite strategy del boton.*/
ButtonSpriteStrategy::~ButtonSpriteStrategy() = default;

/*Alterna entre boton presionado y no presionado.*/
void ButtonSpriteStrategy::switch_sprite(){
    if (this->spriteName == BUTTON_PRESSED){
        this->dynamicSprite = ButtonUnPressedSprite::get_sprite();
        this->spriteName = BUTTON_NOT_PRESSED;
    } else {
        this->dynamicSprite = ButtonPressedSprite::get_sprite();
        this->spriteName = BUTTON_PRESSED;
    }
}