#include "../../../includes/textures/door_texture/door_one_sprite_strategy.h"

#include "../../../includes/textures/door_texture/door_one_closed_sprite.h"
#include "../../../includes/textures/door_texture/door_one_opened_sprite.h"
#include "../../../includes/textures/door_texture/door_one_opening_sprite.h"

#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/area.h"

#include "../../../includes/mixer/sounds_path.h"

/*Inicializa el manejador de sprites de la puerta.*/
DoorOneSpriteStrategy::DoorOneSpriteStrategy()
:   SpriteStrategy(DoorOneClosedSprite::get_sprite()),
    spriteName(DOOR_CLOSE) {}

/*Destruye el manejador de sprites de la puerta.*/
DoorOneSpriteStrategy::~DoorOneSpriteStrategy() = default;

/*
Devuelve el area correspondiente al siguiente sprite 
de la puerta recibida, en la imagen ALL_CHELL_SPRITES de 
images_path.h .
*/
Area DoorOneSpriteStrategy::getNextArea(){
    return std::move(this->dynamicSprite.getNextArea());
}

/*Alterna entre puerta abierta y cerrada.*/
void DoorOneSpriteStrategy::switch_sprite() {
    if (this->spriteName == DOOR_CLOSE){
        this->dynamicSprite = DoorOneOpeningSprite::get_sprite();
        this->spriteName = DOOR_OPENING;
        return;
    }
    if (this->spriteName == DOOR_OPEN){
        this->dynamicSprite = DoorOneOpeningSprite::get_sprite();
        this->dynamicSprite.reverse_sprite();
        this->dynamicSprite.restart();
        this->spriteName = DOOR_CLOSING;
        return;
    }

    if (this->spriteName == DOOR_OPENING){
        this->dynamicSprite.reverse_sprite();
        this->spriteName = DOOR_CLOSING;
        return;
    }

    if (this->spriteName == DOOR_CLOSING){
        this->dynamicSprite.reverse_sprite();
        this->spriteName = DOOR_OPENING;
        return; 
    }
}

/*Actualiza el estado de la puerta.*/
void DoorOneSpriteStrategy::update(){
    if (this->spriteName == DOOR_OPENING){
        if (this->dynamicSprite.is_last_sprite()) { 
            this->dynamicSprite = DoorOneOpenedSprite::get_sprite();
            this->spriteName = DOOR_OPEN;
        }
    }

    if (this->spriteName == DOOR_CLOSING){
        if (this->dynamicSprite.is_last_sprite()) { 
            this->dynamicSprite = DoorOneClosedSprite::get_sprite();
            this->spriteName = DOOR_CLOSE;
        }
    }
    this->dynamicSprite.update();
}