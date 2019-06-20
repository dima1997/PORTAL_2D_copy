#include "../../../includes/textures/rock_texture/rock_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

RockSprite::RockSprite() {}
RockSprite::~RockSprite() = default;

/*
Devuelve un sprite dinamico de roca 1.
IMAGE_PATH : ALL_ROCKS_AND_BALLS
*/
DynamicSprite RockSprite::rock_one(){
    return std::move(DynamicSprite({{3,300}},81,66));
}

/*
Devuelve un sprite dinamico de roca 2.
IMAGE_PATH : ALL_ROCKS_AND_BALLS
*/
DynamicSprite RockSprite::rock_two(){
    return std::move(DynamicSprite({{91,310}},72,53));
}

/*
Devuelve un sprite dinamico de roca 3.
IMAGE_PATH : ALL_ROCKS_AND_BALLS
*/
DynamicSprite RockSprite::rock_three(){
    return std::move(DynamicSprite({{183,305}},64,59));
}

/*
Devuelve un sprite dinamico de roca 4.
IMAGE_PATH : ALL_ROCKS_AND_BALLS
*/
DynamicSprite RockSprite::rock_four(){
    return std::move(DynamicSprite({{267,297}},65,73));
}

/*
Devuelve un sprite dinamico de roca 5.
IMAGE_PATH : ALL_ROCKS_AND_BALLS
*/
DynamicSprite RockSprite::rock_five(){
    return std::move(DynamicSprite({{363,305}},50,59));
}

/*
Devuelve un sprite dinamico de roca 6.
IMAGE_PATH : ALL_ROCKS_AND_BALLS
*/
DynamicSprite RockSprite::rock_six(){
    return std::move(DynamicSprite({{443,312}},65,48));
}

/*
Devuelve un sprite dinamico de roca 7.
IMAGE_PATH : ALL_ROCKS_AND_BALLS
*/
DynamicSprite RockSprite::rock_seven(){
    return std::move(DynamicSprite({{528,300}},56,75));
}

/*
Devuelve un sprite dinamico de roca 8.
IMAGE_PATH : ALL_ROCKS_AND_BALLS
*/
DynamicSprite RockSprite::rock_eight(){
    return std::move(DynamicSprite({{616,305}},54,58));
}