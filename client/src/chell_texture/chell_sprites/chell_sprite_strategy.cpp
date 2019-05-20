#include "chell_sprite_strategy.h"

#include "chell_sweat_right_sprite.h"
#include "chell_run_right_sprite.h"
#include "chell_jump_apex_right_sprite.h"
#include "chell_jump_rise_right_sprite.h"
#include "chell_jump_fall_right_sprite.h"

#include "../../common_texture/dynamic_sprite.h"
#include "../../common_texture/area.h"

#include <memory>

/*Inicializa el estado de sprite de Chell.*/
ChellSpriteStrategy::ChellSpriteStrategy()
:   spriteName(SWEAT_RIGHT), 
    ptrDynamicSprite(
        std::move(
            std::unique_ptr<DynamicSprite>(new ChellSweatRightSprite())
        )
    ),
    keepMoving(false) 
    {}

/*Destruye el estado de sprite de Chell*/
ChellSpriteStrategy::~ChellSpriteStrategy() {}

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
            this->ptrDynamicSprite.reset(new ChellRunRightSprite());
            break;
        case JUMP_APEX_RIGHT:
            this->ptrDynamicSprite.reset(new ChellJumpApexRightSprite());
            break;
        case JUMP_RISE_RIGHT:
            this->ptrDynamicSprite.reset(new ChellJumpRiseRightSprite());
            break;
        case JUMP_FALL_RIGHT:
            this->ptrDynamicSprite.reset(new ChellJumpFallRightSprite());
            break;
        case SWEAT_RIGHT:
            this->ptrDynamicSprite.reset(new ChellSweatRightSprite());
            break;
        default: // igual que case SWEAT_RIGHT
            this->ptrDynamicSprite.reset(new ChellSweatRightSprite());
            break;
    }
}

/*
PRE: Recibe :
    las coordenadas anteriores (int) x,y de Chell.
    las coordenadas nuevas (int) x,y de Chell.
POST: actualiza el sprite actual de Chell.
*/
void ChellSpriteStrategy::move(float xBefore, float yBefore,float xNow, float yNow){
    spriteNameStrategy_t spriteBefore = this->spriteName; 

    if ((xBefore == xNow) && (yBefore != yNow)){
        this->setSpriteStrategy(JUMP_APEX_RIGHT);
        this->keepMoving = true;
        return;
    }

    if (yBefore < yNow){
        this->setSpriteStrategy(JUMP_RISE_RIGHT);
        this->keepMoving = true;
        return;
    } 

    if (yBefore > yNow){ 
        this->setSpriteStrategy(JUMP_FALL_RIGHT);
        this->keepMoving = true;
        return;  
    }

    if (xBefore != xNow){
        this->setSpriteStrategy(RUN_RIGHT);
        this->keepMoving = true;
        return;
    }

    this->setSpriteStrategy(SWEAT_RIGHT);
    this->keepMoving = false;
    return;
}

/*
Devuelve el area correspondiente al siguiente sprite de Chell, 
en la imagen ALL_CHELL_IMAGE de images_path.h .
*/
Area ChellSpriteStrategy::getNextArea(){
    // Si se usa en distintos hilos necesitare colocar mutex
    if (this->keepMoving) { 
        keepMoving = false; 
    } else {
        this->setSpriteStrategy(SWEAT_RIGHT);
    }
    DynamicSprite & actualSprite = *(this->ptrDynamicSprite);
    return std::move(actualSprite.getNextArea());
}
