#ifndef BUTTON_SPRITE_STRATEGY_H
#define BUTTON_SPRITE_STRATEGY_H

#include "../common_texture/sprite_strategy.h"

enum ButtonSpriteName {
    BUTTON_NOT_PRESSED,
    BUTTON_PRESSED,
};

class ButtonSpriteStrategy : public SpriteStrategy {
private: 
    ButtonSpriteName spriteName;
public:
    /*
    Iniciliza un boton sprite strategy, cuyos sprites 
    se encuentran en la imagen BUTTON_SPRITE de 
    images_paths.h .
    */
    ButtonSpriteStrategy();

    /*Destruye el sprite strategy del boton.*/
    virtual ~ButtonSpriteStrategy();

    /*
    Alterna el sprite del boton entre presionado 
    y no presionado.
    */
    virtual void switch_sprite();
};

#endif // BUTTON_SPRITE_STRATEGY_H