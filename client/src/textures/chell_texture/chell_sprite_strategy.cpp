#include "../../../includes/textures/chell_texture/chell_sprite_strategy.h"

#include "../../../includes/textures/chell_texture/chell_stand_right_sprite.h"
#include "../../../includes/textures/chell_texture/chell_run_right_sprite.h"
#include "../../../includes/textures/chell_texture/chell_jump_apex_right_sprite.h"
#include "../../../includes/textures/chell_texture/chell_jump_rise_right_sprite.h"
#include "../../../includes/textures/chell_texture/chell_jump_fall_right_sprite.h"
#include "../../../includes/textures/chell_texture/chell_point_right_sprite.h"

#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"
#include "../../../includes/textures/common_texture/area.h"

#include "../../../includes/mixer/sounds_path.h"

#define CHELL_FRAMES_WAIT 23
#define CHELL_POINT_FRAMES_WAIT 5
#define DELTA_POINT 0.5

/*Inicializa el estado de sprite de Chell.*/
ChellSpriteStrategy::ChellSpriteStrategy()
:   SpriteStrategy(
        ChellStandRightSprite::get_sprite()
    ),
    spriteName(STAND_RIGHT), 
    keepMoving(false),
    framesWait(0),
    framesPointWait(0)
    {}

/*Destruye el estado de sprite de Chell*/
ChellSpriteStrategy::~ChellSpriteStrategy() = default;

/*
PRE: Recibe un nombre de sprite strategy (spriteNameStrategy_t).
POST: Setea el sprite actual al recibido, si que no esta ya seteado.
*/
void ChellSpriteStrategy::setSpriteStrategy(spriteNameStrategy_t newSpriteName){
    if (newSpriteName != STAND_RIGHT){
        this->keepMoving = true;
    }
    if (this->spriteName == newSpriteName){
        return;
    }
    if (this->framesPointWait > 0){
        return;
    }
    this->spriteName = newSpriteName;
    switch (newSpriteName){
        case RUN_RIGHT:
            this->dynamicSprite = ChellRunRightSprite::get_sprite();
            break;
        case JUMP_APEX_RIGHT:
            this->dynamicSprite = ChellJumpApexRightSprite::get_sprite();
            break;
        case JUMP_RISE_RIGHT:
            this->dynamicSprite = ChellJumpRiseRightSprite::get_sprite();
            break;
        case JUMP_FALL_RIGHT:
            this->dynamicSprite = ChellJumpFallRightSprite::get_sprite();
            break;
        case STAND_RIGHT:
            this->dynamicSprite = ChellStandRightSprite::get_sprite();
            break;
        case POINT_RIGHT:
            this->dynamicSprite = ChellPointRightSprite::point_right();
            this->framesPointWait = CHELL_POINT_FRAMES_WAIT;
            break;
        case POINT_RIGHT_UP:
            this->dynamicSprite = ChellPointRightSprite::point_right_up();
            this->framesPointWait = CHELL_POINT_FRAMES_WAIT;
            break;
        case POINT_RIGHT_DOWN:
            this->dynamicSprite = ChellPointRightSprite::point_right_down();
            this->framesPointWait = CHELL_POINT_FRAMES_WAIT;
            break;
        case POINT_UP:
            this->dynamicSprite = ChellPointRightSprite::point_up();
            this->framesPointWait = CHELL_POINT_FRAMES_WAIT;
            break;
        case POINT_DOWN:
            this->dynamicSprite = ChellPointRightSprite::point_down();
            this->framesPointWait = CHELL_POINT_FRAMES_WAIT;
            break;
        default: // igual que case STAND_RIGHT
            this->dynamicSprite = ChellStandRightSprite::get_sprite();
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
        newName = STAND_RIGHT;
    }
    // Seguir haciendo esto luego de setear los sonidos
    this->setSpriteStrategy(newName); 
    return;
}

/*
Devuelve el area correspondiente al siguiente sprite de Chell, 
en la imagen ALL_CHELL_IMAGE de images_path.h .
*/
Area ChellSpriteStrategy::getNextArea(){
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
        if ((sounds.size()) != 0 && (sounds.back() == SOUND_JUMP)){
            return;
        } 
        sounds.push_back(SOUND_JUMP);
    }
}

/*Actualiza el sprite al siguiente a ser usado.*/
void ChellSpriteStrategy::update(){
    this->dynamicSprite.update();
    if (this->framesWait > 0){
        --this->framesWait;
    }
    if (this->framesPointWait > 0){
        --this->framesPointWait;
        return;
    }
    if (this->keepMoving) { 
        this->keepMoving = false;
    } else {
        this->setSpriteStrategy(STAND_RIGHT);
    }
}

/*
PRE: Recibe :
    las coordenadas actuales (int) x,y de Chell.
    las coordenadas del punto (int) x,y a donde Chell esta 
    apuntando.
POST: actualiza el sprite actual de Chell.
*/
void ChellSpriteStrategy::point(float xNow, float yNow, float xPoint, float yPoint){
    if ((xNow > xPoint + DELTA_POINT) || (xNow < xPoint - DELTA_POINT)){
        if (yNow < yPoint - DELTA_POINT){
            this->setSpriteStrategy(POINT_RIGHT_UP);
            return;
        }
        if (yNow > yPoint + DELTA_POINT){
            this->setSpriteStrategy(POINT_RIGHT_DOWN);
            return;
        }
        this->setSpriteStrategy(POINT_RIGHT);
        return;
    }
    if (yNow < yPoint){
        this->setSpriteStrategy(POINT_UP);
        return;
    }

    if (yNow > yPoint){
        this->setSpriteStrategy(POINT_DOWN);
        return;
    } 
    // no deberia pasar que apunte hacia su centro de coordenadas
}