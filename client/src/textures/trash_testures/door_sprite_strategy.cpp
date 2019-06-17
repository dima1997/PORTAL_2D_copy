#include "../../../includes/textures/chell_texture/chell_dead_strategy.h"

#include "../../../includes/textures/chell_texture/chell_dying_sprite.h"

#include "../../../includes/textures/common_texture/null_sprite.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/area.h"

#include "../../../includes/mixer/sounds_path.h"

/*Inicializa el manejador de sprites de la puerta.*/
DoorOneSpriteStrategy::DoorOneSpriteStrategy()
:   SpriteStrategy(DoorOneClosed::get_sprite()),
    spriteName(DOOR_CLOSED) {}

/*Destruye el manejador de sprites de la puerta.*/
DoorOneSpriteStrategy::~DoorOneSpriteStrategy() = default;

/*
Devuelve el area correspondiente al siguiente sprite 
de la puerta recibida, en la imagen ALL_CHELL_SPRITES de 
images_path.h .
*/
Area DoorOneSpriteStrategy::getNextArea(){
    if (this->spriteName == DOOR_OPENING){
        if (this->dynamicSprite.is_last_sprite()) { 
            this->dynamicSprite = DoorOneOpened::get_sprite();
            this->spriteName = DOOR_OPEN;
        }
    }

    if (this->spriteName == DOOR_CLOSING){
        if (this->dynamicSprite.is_last_sprite()) { 
            this->dynamicSprite = DoorOneClosed::get_sprite();
            this->spriteName = DOOR_CLOSE;
        }
    }
    
    return std::move(this->dynamicSprite.getNextArea());
}

/*Alterna entre puerta abierta y cerrada.*/
void DoorOneSpriteStrategy::switch_sprite() {

}