#ifndef CHELL_SPRITE_STRATEGY_H
#define CHELL_SPRITE_STRATEGY_H

#include "../common_texture/sprite_strategy.h"
#include "../common_texture/dynamic_sprite.h"
#include "../common_texture/area.h"

#include "../../mixer/sounds_path.h"

#include "../../render_time.h" 

enum spriteNameStrategy_t {
    STAND_RIGHT,
    RUN_RIGHT,
    JUMP_APEX_RIGHT,
    JUMP_RISE_RIGHT,
    JUMP_FALL_RIGHT,
    POINT_RIGHT,
    POINT_RIGHT_UP,
    POINT_RIGHT_DOWN,
    POINT_UP,
    POINT_DOWN
};

class ChellSpriteStrategy : public SpriteStrategy {
private:
    spriteNameStrategy_t spriteName;
    bool keepMoving;
    int framesWait; 
    int framesPointWait;
    
    /*
    PRE: Recibe un nombre de sprite strategy (spriteNameStrategy_t).
    POST: Setea el sprite actual al recibido, si que no esta ya seteado.
    */
    void setSpriteStrategy(spriteNameStrategy_t newSpriteName);

    /*
    PRE: Recibe el nombre del nuevo sprite de chell, 
    aun sin asignar, y un vector de nombres de sonidos.
    POST: Setea un el sonido en correspondiente al 
    nuevo nombre de sprite, si es que no tiene dicho
    nombre ya.
    */
    void setSound(spriteNameStrategy_t newSpriteName, 
                  std::vector<SOUND_NAME> & sounds);    
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
                      float xNow, float yNow,
                      std::vector<SOUND_NAME> & sounds) override;

    /*Por ahora no hace nada*/
    virtual void switch_sprite() {}

    /*
    Devuelve el area correspondiente al siguiente sprite de Chell, 
    en la imagen ALL_CHELL_IMAGE de images_path.h .
    */
    virtual Area getNextArea() override;


    /*Actualiza el sprite al siguiente a ser usado.*/
    virtual void update();

    /*
    PRE: Recibe :
        las coordenadas actuales (int) x,y de Chell.
        las coordenadas del punto (int) x,y a donde Chell esta 
        apuntando.
    POST: actualiza el sprite actual de Chell.
    */
    virtual void point(float xNow, float yNow, float xPoint, float yPoint);
};

#endif // CHELL_SPRITE_STATE_H
