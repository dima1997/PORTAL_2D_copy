#include "../../../includes/textures/rock_texture/rock_one_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

RockOneSprite::RockOneSprite() {}
RockOneSprite::~RockOneSprite() = default;

/*
Devuelve un sprite dinamico de roca 1.
IMAGE_PATH : ALL_ROCKS_AND_BALLS
*/
DynamicSprite RockOneSprite::get_sprite(){
    return std::move(DynamicSprite({{517,4513}},85,83));
}