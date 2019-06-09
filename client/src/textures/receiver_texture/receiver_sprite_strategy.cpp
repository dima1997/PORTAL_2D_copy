#include "../../../includes/textures/receiver_texture/receiver_sprite_strategy.h"

#include "../../../includes/textures/receiver_texture/receiver_on_sprite.h"
#include "../../../includes/textures/receiver_texture/receiver_off_sprite.h"
#include "../../../includes/textures/receiver_texture/receiver_unlocking_sprite.h"

#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"

#include <memory>

/*
Iniciliza un recibidor sprite strategy, cuyos sprites 
se encuentran en la imagen ALL_BLOCKS_SPRITES de 
images_paths.h .
*/
ReceiverSpriteStrategy::ReceiverSpriteStrategy() 
:   SpriteStrategy(
        ReceiverOffSprite::get_sprite()
    ), 
    spriteName(RECEIVER_OFF) {}
/*
:   SpriteStrategy(
        std::move(
            std::unique_ptr<DynamicSprite>(new ReceiverOffSprite())
        )
    )    
    , spriteName(RECEIVER_OFF) {}
*/

/*Destruye uel sprite strategy del portal.*/
ReceiverSpriteStrategy::~ReceiverSpriteStrategy() = default;

/*Alterna entre recibidor bloqueando y desbloqueado*/
void ReceiverSpriteStrategy::switch_sprite(){
    if (this->spriteName == RECEIVER_OFF){
        //this->ptrDynamicSprite.reset(new ReceiverUnlockingSprite());
        this->dynamicSprite = ReceiverUnlockingSprite::get_sprite();
        this->spriteName = RECEIVER_UNLOCKING;
    } else {
        //this->ptrDynamicSprite.reset(new ReceiverOffSprite());
        this->dynamicSprite = ReceiverOffSprite::get_sprite();
        this->spriteName = RECEIVER_OFF;
    }
}

/*
Devuelve el area correspondiente al siguiente sprite de la textura que 
representa, en la imagen.png correspondiente.
*/
Area ReceiverSpriteStrategy::getNextArea(){
    if (this->spriteName == RECEIVER_UNLOCKING){
        //if (this->ptrDynamicSprite->is_last_sprite()){
        if (this->dynamicSprite.is_last_sprite()){
            //this->ptrDynamicSprite.reset(new ReceiverOnSprite());
            this->dynamicSprite = ReceiverOnSprite::get_sprite();
            this->spriteName = RECEIVER_ON;
        }
    }
    /*
    DynamicSprite & actualSprite = *(this->ptrDynamicSprite);
    return std::move(actualSprite.getNextArea());
    */
    return std::move(this->dynamicSprite.getNextArea());
}