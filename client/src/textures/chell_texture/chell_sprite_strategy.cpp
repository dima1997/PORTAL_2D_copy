#include "../../../includes/textures/chell_texture/chell_sprite_strategy.h"

#include "../../../includes/textures/chell_texture/chell_sweat_right_sprite.h"
#include "../../../includes/textures/chell_texture/chell_run_right_sprite.h"
#include "../../../includes/textures/chell_texture/chell_jump_apex_right_sprite.h"
#include "../../../includes/textures/chell_texture/chell_jump_rise_right_sprite.h"
#include "../../../includes/textures/chell_texture/chell_jump_fall_right_sprite.h"

#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"
#include "../../../includes/textures/common_texture/area.h"

#include "../../../includes/mixer/sounds_path.h"

#include <memory>

/*Inicializa el estado de sprite de Chell.*/
ChellSpriteStrategy::ChellSpriteStrategy()
:   SpriteStrategy(
        ChellSweatRightSprite::get_sprite()
    ),
    spriteName(SWEAT_RIGHT), 
    keepMoving(false) 
    {}
/*
:   SpriteStrategy(
        std::move(std::unique_ptr<DynamicSprite>(new ChellSweatRightSprite()))
    ),
    spriteName(SWEAT_RIGHT), 
    keepMoving(false) 
    {}
*/
/*Destruye el estado de sprite de Chell*/
ChellSpriteStrategy::~ChellSpriteStrategy() = default;

/*
PRE: Recibe un nombre de sprite strategy (spriteNameStrategy_t).
POST: Setea el sprite actual al recibido, si que no esta ya seteado.
*/
void ChellSpriteStrategy::setSpriteStrategy(spriteNameStrategy_t newSpriteName){
    if (this->spriteName == newSpriteName){
        return;
    }
    this->spriteName = newSpriteName;
    switch (newSpriteName){
        case RUN_RIGHT:
            //this->ptrDynamicSprite.reset(new ChellRunRightSprite());
            this->dynamicSprite = ChellRunRightSprite::get_sprite();
            break;
        case JUMP_APEX_RIGHT:
            //this->ptrDynamicSprite.reset(new ChellJumpApexRightSprite());
            this->dynamicSprite = ChellJumpApexRightSprite::get_sprite();
            break;
        case JUMP_RISE_RIGHT:
            //this->ptrDynamicSprite.reset(new ChellJumpRiseRightSprite());
            this->dynamicSprite = ChellJumpRiseRightSprite::get_sprite();
            break;
        case JUMP_FALL_RIGHT:
            //this->ptrDynamicSprite.reset(new ChellJumpFallRightSprite());
            this->dynamicSprite = ChellJumpFallRightSprite::get_sprite();
            break;
        case SWEAT_RIGHT:
            //this->ptrDynamicSprite.reset(new ChellSweatRightSprite());
            this->dynamicSprite = ChellSweatRightSprite::get_sprite();
            break;
        default: // igual que case SWEAT_RIGHT
            //this->ptrDynamicSprite.reset(new ChellSweatRightSprite());
            this->dynamicSprite = ChellSweatRightSprite::get_sprite();
            break;
    }
}

/*
PRE: Recibe :
    las coordenadas anteriores (int) x,y de Chell.
    las coordenadas nuevas (int) x,y de Chell.
POST: actualiza el sprite actual de Chell.
*/
void ChellSpriteStrategy::move(float xBefore, float yBefore, float xNow, float yNow,
    std::vector<SOUND_NAME> & sounds){
    if (yBefore < yNow){
        spriteNameStrategy_t jumpName = JUMP_APEX_RIGHT;
        this->setSound(jumpName,sounds);
    }
    spriteNameStrategy_t newName = this->spriteName;
    if ((xBefore == xNow) && (yBefore != yNow)){
        newName = JUMP_APEX_RIGHT;
    } else if (yBefore < yNow){
        newName = JUMP_RISE_RIGHT;
    } else if (yBefore > yNow){ 
        newName = JUMP_FALL_RIGHT;
    } else if (xBefore != xNow){
        newName = RUN_RIGHT;
    } else {
        newName = SWEAT_RIGHT;
    }
    // Seguir haciendo esto luego de setear los sonidos
    this->setSpriteStrategy(newName); 
    if (newName != SWEAT_RIGHT){
        this->keepMoving = true;
    }  
    return;
}

/*
Devuelve el area correspondiente al siguiente sprite de Chell, 
en la imagen ALL_CHELL_IMAGE de images_path.h .
*/
Area ChellSpriteStrategy::getNextArea(){
    if (this->framesWait > 0){
        --this->framesWait;
    }
    if (this->keepMoving) { 
        this->keepMoving = false;
    } else {
        this->setSpriteStrategy(SWEAT_RIGHT);
    }
    /*
    DynamicSprite & actualSprite = *(this->ptrDynamicSprite);
    return std::move(actualSprite.getNextArea());
    */
    return std::move(this->dynamicSprite.getNextArea());
}

/*
PRE: Recibe el nombre del nuevo sprite de chell, 
aun sin asignar, y un vector de nombres de sonidos.
POST: Setea un el sonido en correspondiente al 
nuevo nombre de sprite, si es que no tiene dicho
nombre ya.
*/
void ChellSpriteStrategy::setSound(spriteNameStrategy_t newSpriteName, 
                                   std::vector<SOUND_NAME> & sounds) {
    if (this->spriteName == newSpriteName){
        return;
    }
    
    if (this->framesWait > 0){
        return;
    }
    
    this->framesWait = CHELL_FRAMES_WAIT;
    if (newSpriteName == JUMP_APEX_RIGHT){
        // Para evitar repetir sonidos cuando Chell 
        // cambia en un instante su sprite por default
        // Funciona para dos sonidos iguales que deben
        // ser reproducidos, porque se reproduciran en
        // en ciclos distintos
        if ((sounds.size()) != 0 && (sounds.back() == SOUND_JUMP)){
            return;
        } 
        sounds.push_back(SOUND_JUMP);
    }
}