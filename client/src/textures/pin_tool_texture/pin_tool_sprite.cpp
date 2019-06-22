#include "../../../includes/textures/pin_tool_texture/pin_tool_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

PinToolSprite::PinToolSprite() {}
PinToolSprite::~PinToolSprite() = default;

/*
Devuelve el sprite dinamico del pin tool.
IMAGE_PATH : PIN_TOOL_SPRITES
*/
DynamicSprite PinToolSprite::get_sprite(){
    return DynamicSprite({{0,0}},178,202);
}
