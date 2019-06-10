#ifndef PIN_TOOL_SPRITE_STRATEGY_H
#define PIN_TOOL_SPRITE_STRATEGY_H

#include "../common_texture/sprite_strategy.h"

enum PinToolSpriteName {
    PIN_TOOL_ON,
    PIN_TOOL_OFF
};

class PinToolSpriteStrategy : public SpriteStrategy {
private:
    PinToolSpriteName spriteName;
public:
    /*Inicializa un manejador de sprites de la pin tool*/
    PinToolSpriteStrategy();

    /*Destruye el manejador de sprites de la pin tool.*/
    virtual ~PinToolSpriteStrategy();

    /*Alterna entre pin tool visible y no visible.*/
    virtual void switch_sprite();
};

#endif // PIN_TOOL_SPRITE_STRATEGY_H
