#include "chell_sprite_state.h"

#include "chell_sweat_sprite.h"
#include "chell_running_sprite.h"

/*Inicializa el estado de sprite de Chell.*/
ChellSpriteState::ChellSpriteState()
:   spriteName(SWEAT), 
    ptrDynamicSprite(
        std::move(
            std::unique_ptr<DynamicSprite>(new ChellSweatSprite())
        )
    ),
    keepMoving(false) 
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
    spriteNameStrategy_t spriteBefore = this->spriteName; 
    if (xBefore != xNow){
        this->spriteName = RUNNING;
        if (spriteBefore != this->spriteName){
            this->ptrDynamicSprite.reset(new ChellRunningSprite());
        }
        this->keepMoving = true; //Tal vez necesite mutex
    } else {
        this->spriteName = SWEAT;
        if (spriteBefore != this->spriteName){
            this->ptrDynamicSprite.reset(new ChellSweatSprite());
        }
        this->keepMoving = false; //Tal vez necesite mutex
    }
}

/*
Devuelve el area correspondiente al siguiente sprite de Chell, 
en la imagen ALL_CHELL_IMAGE de images_path.h .
*/
Area ChellSpriteState::getNextArea(){
    // Si se usa en distintos hilos necesitare colocar mutex
    if (this->keepMoving) { 
        keepMoving = false; 
    } else {
        if (this->spriteName != SWEAT){
            this->spriteName = SWEAT;
            this->ptrDynamicSprite.reset(new ChellSweatSprite()); 
        }
    }
    DynamicSprite & actualSprite = *(this->ptrDynamicSprite);
    return std::move(actualSprite.getNextArea());
}
