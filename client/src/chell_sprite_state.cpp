#include "chell_sprite_state.h"

/*Inicializa el estado de sprite de Chell.*/
ChellSpriteState::ChellSpriteState()
:   dynamicSprites(
        {
            {SWEAT, ChellSweatSprite()},
            {RUNNING, ChellRunningSprite()}
        }
    ),
    SWEAT
    {}

/*Destruye el estado de sprite de Chell*/
ChellSpriteState::~ChellSpriteState(){}

/*
PRE: Recibe :
    las coordenadas anteriores (int) x,y de Chell.
    las coordenadas nuevas (int) x,y de Chell.
POST: actualiza el sprite actual de Chell.
*/
ChellSpriteState::move(float xBefore, float yBefore,float xNow, float yNow){
    spriteState_t stateBefore = this->actualState; 
    if (xBefore != xNow){
        this->actualState = RUNNING;
    } else {
        this->actualState = SWEAT;
    }
    if (stateBefore != this->actualState) {
        this->dynamicSprites[this->actualState].restart();
    }
}

/*
Devuelve el area correspondiente al siguiente sprite de Chell, 
en la imagen ALL_CHELL_IMAGE de images_path.h .
*/
Area ChellSpriteState::getNextArea(){
    DynamicSprite & actualSprite = this->dinamicSprites[this->actualState];
    return std::move(actualSprite.getNextArea());
}
