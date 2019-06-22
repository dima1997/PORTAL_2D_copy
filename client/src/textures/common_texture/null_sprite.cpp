#include "../../../includes/textures/common_texture/null_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

NullSprite::NullSprite() {}
NullSprite::~NullSprite() = default;

/*Devuelve un sprite dinamico nulo (sin imagen).*/
DynamicSprite NullSprite::get_sprite(){
    return DynamicSprite({{0,0}},0,0);
} 
