#ifndef CHELL_SPRITE_STRATEGY_H
#define CHELL_SPRITE_STRATEGY_H

#include "../common_texture/sprite_strategy.h"
#include "../common_texture/dynamic_sprite.h"
#include "../common_texture/area.h"

#include <memory>

enum spriteNameStrategy_t {
    SWEAT_RIGHT,
    RUN_RIGHT,
    JUMP_APEX_RIGHT,
    JUMP_RISE_RIGHT,
    JUMP_FALL_RIGHT,
};

class ChellSpriteStrategy : public SpriteStrategy {
private:
    spriteNameStrategy_t spriteName;
    bool keepMoving;
    
    /*
    PRE: Recibe un nombre de sprite strategy (spriteNameStrategy_t).
    POST: Setea el sprite actual al recibido, si que no esta ya seteado.
    */
    void setSpriteStrategy(spriteNameStrategy_t newSpriteName);

public:
    /*Inicializa el estado de sprite de Chell.*/
    ChellSpriteStrategy();

    /*Destruye el estado de sprite de Chell*/
    ~ChellSpriteStrategy();

    /*
    PRE: Recibe :
        las coordenadas anteriores (int) x,y de Chell.
        las coordenadas nuevas (int) x,y de Chell.
    POST: actualiza el sprite actual de Chell.
    */
    virtual void move(float xBefore, float yBefore, 
                        float xNow, float yNow) override;

    /*Por ahora no hace nada*/
    virtual void switch_sprite() {}

    /*
    Devuelve el area correspondiente al siguiente sprite de Chell, 
    en la imagen ALL_CHELL_IMAGE de images_path.h .
    */
    virtual Area getNextArea() override;    
};

#endif // CHELL_SPRITE_STATE_H
