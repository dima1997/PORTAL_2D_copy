#ifndef SPRITE_STRATEGY_H
#define SPRITE_STRATEGY_H

#include "dynamic_sprite.h"
#include "area.h"
#include "../../mixer/sounds_path.h"

#include <memory>

class SpriteStrategy {
protected:
    DynamicSprite dynamicSprite;

public:
    /*
    PRE: Recibe un sprite dinamico 
    POST: Inicializa un SpriteStrategy que alterna los 
    sprites del DynamicSprite recibido, uno a uno.
    */
    SpriteStrategy(DynamicSprite dynamicSprite);
    
    /*Destruye el sprite strategy.*/
    virtual ~SpriteStrategy();
    
    /*
    PRE: Recibe :
        las coordenadas anteriores (int) x,y de la textura que representa.
        las coordenadas nuevas (int) x,y de la textura que representa.
    POST: No hace nada.
    */
    virtual void move(float xBefore, float yBefore, float xNow, float yNow);

    /*
    PRE: Recibe :
        las coordenadas anteriores (int) x,y de la textura que representa.
        las coordenadas nuevas (int) x,y de la textura que representa.
        un vector de nombre de sonidos
    POST: No hace nada.
    */
    virtual void move(float xBefore, float yBefore, float xNow, float yNow, 
                          std::vector<SOUND_NAME> & sounds);
    
    /*No hace nada.*/
    virtual void switch_sprite();
    
    /*
    Devuelve el area correspondiente al siguiente 
    sprite de la textura que representa, en la 
    imagen.png correspondiente.
    */
    virtual Area getNextArea();  

    /*Actualiza el sprite al siguiente a ser usado.*/
    virtual void update();

    /*
    PRE: Recibe :
        las coordenadas actuales (int) x,y de la textura.
        las coordenadas del punto (int) x,y a donde la textura 
        esta apuntando.
    POST: actualiza el sprite actual.
    */
    virtual void point(float xNow, float yNow, float xPoint, float yPoint);
};

#endif // SPRITE_STRATEGY_H
