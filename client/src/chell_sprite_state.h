#ifndef CHELL_SPRITE_STATE_H
#define CHELL_SPRITE_STATE_H

#include "dynamic_sprite.h"
#include "area.h"

#include <memory>

enum spriteNameStrategy_t {
    SWEAT,
    RUNNING
};

class ChellSpriteState {
private:
    spriteNameStrategy_t spriteName;
    std::unique_ptr<DynamicSprite> ptrDynamicSprite;
    bool keepMoving;
public:
    /*Inicializa el estado de sprite de Chell.*/
    ChellSpriteState();

    /*Destruye el estado de sprite de Chell*/
    ~ChellSpriteState();

    /*
    PRE: Recibe :
        las coordenadas anteriores (int) x,y de Chell.
        las coordenadas nuevas (int) x,y de Chell.
    POST: actualiza el sprite actual de Chell.
    */
    void move(float xBefore, float yBefore, float xNow, float yNow);

    /*
    Devuelve el area correspondiente al siguiente sprite de Chell, 
    en la imagen ALL_CHELL_IMAGE de images_path.h .
    */
    Area getNextArea();    
};

#endif // CHELL_SPRITE_STATE_H
