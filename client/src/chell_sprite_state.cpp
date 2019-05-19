#include "chell_sprite_state.h"

#include "chell_sweat_sprite.h"
#include "chell_running_sprite.h"

/*Inicializa el estado de sprite de Chell.*/
ChellSpriteState::ChellSpriteState()
:   actualSprite(SWEAT), 
    ptrDynamicSprite(
        std::move(
            std::unique_ptr<DynamicSprite>(new ChellSweatSprite())
        )
    ) 
    {}

/*Destruye el estado de sprite de Chell*/
ChellSpriteState::~ChellSpriteState() {}

/*
PRE: Recibe :
    las coordenadas anteriores (int) x,y de Chell.
    las coordenadas nuevas (int) x,y de Chell.
POST: actualiza el sprite actual de Chell.
*/
void ChellSpriteState::move(float xBefore, float yBefore,float xNow, float yNow){
    spriteStrategy_t spriteBefore = this->actualSprite; 
    if (xBefore != xNow){
        this->actualSprite = RUNNING;
        if (spriteBefore != this->actualSprite){
            this->ptrDynamicSprite.reset(new ChellRunningSprite());
        }
    } else {
        this->actualSprite = SWEAT;
        if (spriteBefore != this->actualSprite){
            this->ptrDynamicSprite.reset(new ChellSweatSprite());
        }
    }
}

/*
Devuelve el area correspondiente al siguiente sprite de Chell, 
en la imagen ALL_CHELL_IMAGE de images_path.h .
*/
Area ChellSpriteState::getNextArea(){
    DynamicSprite & actualSprite = *(this->ptrDynamicSprite);
    return std::move(actualSprite.getNextArea());
}
