#include "chell_sprite_strategy.h"

#include "chell_sweat_right_sprite.h"
#include "chell_run_right_sprite.h"

/*Inicializa el estado de sprite de Chell.*/
ChellSpriteStrategy::ChellSpriteStrategy()
:   spriteName(SWEAT), 
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
PRE: Recibe :
    las coordenadas anteriores (int) x,y de Chell.
    las coordenadas nuevas (int) x,y de Chell.
POST: actualiza el sprite actual de Chell.
*/
void ChellSpriteStrategy::move(float xBefore, float yBefore,float xNow, float yNow){
    spriteNameStrategy_t spriteBefore = this->spriteName; 
    if (xBefore != xNow){
        this->spriteName = RUNNING;
        if (spriteBefore != this->spriteName){
            this->ptrDynamicSprite.reset(new ChellRunRightSprite());
        }
        this->keepMoving = true; //Tal vez necesite mutex
    } else {
        this->spriteName = SWEAT;
        if (spriteBefore != this->spriteName){
            this->ptrDynamicSprite.reset(new ChellSweatRightSprite());
        }
        this->keepMoving = false; //Tal vez necesite mutex
    }
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
        if (this->spriteName != SWEAT){
            this->spriteName = SWEAT;
            this->ptrDynamicSprite.reset(new ChellSweatRightSprite()); 
        }
    }
    DynamicSprite & actualSprite = *(this->ptrDynamicSprite);
    return std::move(actualSprite.getNextArea());
}
