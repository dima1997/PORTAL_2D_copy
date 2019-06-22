#include "../../../includes/textures/chell_texture/chell_point_right_sprite.h"

ChellPointRightSprite::ChellPointRightSprite() {}
ChellPointRightSprite::~ChellPointRightSprite() = default;

/*
Devuelve sprite de Chell apuntando a derecha.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellPointRightSprite::point_right(){
    return std::move(DynamicSprite({{28,2977}},148,216));
}

/*
Devuelve sprite de Chell apuntando ariba.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellPointRightSprite::point_up(){
    return DynamicSprite({{214,2985}},113,210);
}

/*
Devuelve sprite de Chell apuntando arriba y a derecha.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellPointRightSprite::point_right_up(){
    return DynamicSprite({{593,2982}},119,201);
}

/*
Devuelve sprite de Chell apuntando abajo.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellPointRightSprite::point_down(){
    return DynamicSprite({{634,2762}},139,188);
}

/*
Devuelve sprite de Chell apuntando abajo y a derecha.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellPointRightSprite::point_right_down(){
    return DynamicSprite({{295,1342}},134,220);
}
