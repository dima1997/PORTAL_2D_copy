#ifndef PIN_TOOL_SPRITE_H
#define PIN_TOOL_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class PinToolSprite {
public:
    /*Inicializa un pin tool sprite.*/
    PinToolSprite();

    /*Destruye el pin tool sprite*/
    virtual ~PinToolSprite();

    /*Devuelve el sprite dinamico del pin tool*/
    static DynamicSprite get_sprite();
};

#endif // PIN_TOOL_SPRITE_H
