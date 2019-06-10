#include "../../../includes/textures/pin_tool_texture/pin_tool_sprite_strategy.h"

#include "../../../includes/textures/pin_tool_texture/pin_tool_sprite.h"

#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"
#include "../../../includes/textures/common_texture/null_sprite.h"

/*Inicializa un manejador de sprites de la pin tool*/
PinToolSpriteStrategy::PinToolSpriteStrategy()
:   SpriteStrategy(PinToolSprite::get_sprite()),
    spriteName(PIN_TOOL_ON) {}

/*Destruye el manejador de sprites de la pin tool.*/
PinToolSpriteStrategy::~PinToolSpriteStrategy() = default;

/*Alterna entre pin tool visible y no visible.*/
void PinToolSpriteStrategy::switch_sprite(){
    if (this->spriteName == PIN_TOOL_ON){
        this->dynamicSprite = NullSprite::get_sprite();
        this->spriteName = PIN_TOOL_OFF;
    } else {
        this->dynamicSprite = PinToolSprite::get_sprite();
        this->spriteName = PIN_TOOL_ON;
    }
}