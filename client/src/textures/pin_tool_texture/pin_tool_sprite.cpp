#include "../../../includes/textures/pin_tool_texture/pin_tool_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*Inicializa un pin tool sprite.*/
PinToolSprite::PinToolSprite(){}

/*Destruye el pin tool sprite*/
PinToolSprite::~PinToolSprite() = default;

/*Devuelve el sprite dinamico del pin tool*/
DynamicSprite PinToolSprite::get_sprite(){
    return std::move(DynamicSprite({{0,0}},178,202));
}
