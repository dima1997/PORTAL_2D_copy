#ifndef SPRITE_STRATEGY_H
#define SPRITE_STRATEGY_H

#include "dynamic_sprite.h"
#include "area.h"

class SpriteStrategy{
private:
    std::unique_ptr<DynamicSprite> ptrDynamicSprite;
public:
    /*
    PRE: Recibe un puntero unico a un sprite dinamico 
    (std::unique_ptr<DynamicSprite>)
    POST: Inicializa un SpriteStrategy que alterna los 
    sprites del DynamicSprite recibido, uno a uno.
    */
    SpriteStrategy(std::unique_ptr<DynamicSprite> ptrDynamicSprite);
    
    /*Destruye el sprite strategy.*/
    ~SpriteStrategy();
    /*
    PRE: Recibe :
        las coordenadas anteriores (int) x,y de la textura que representa.
        las coordenadas nuevas (int) x,y de la textura que representa.
    POST: No hace nada.
    */
    void move(float xBefore, float yBefore, float xNow, float yNow);
    
    /*No hace nada.*/
    void switch();
    
    /*
    Devuelve el area correspondiente al siguiente sprite de la textura que 
    representa, en la imagen.png correspondiente.
    */
    Area getNextArea();  
};

#endif // SPRITE_STRATEGY_H