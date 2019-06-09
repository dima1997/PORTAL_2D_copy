#ifndef SPRITE_CREATOR_H
#define SPRITE_CREATOR_H

#include "dynamic_sprite.h"

class SpriteCreator {
private:
    DynamicSprite dynamicSprite;
    
public:
    /*
    PRE: Recibe un sprite dinamico (DynamicSprite) 
    POST: Inicializo un creador de sprites de dicho
    sprite recido.
    */
    SpriteCreator(DynamicSprite dynamicSprite);

    /*Destruye el creador de sprites dinamicos.*/
    virtual ~SpriteCreator();

    /*Devuelve el sprite dynamico de este creador.*/
    virtual DynamicSprite get_sprite();

#endif // SPRITE_CREATOR_H
