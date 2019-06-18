#include "../../../includes/textures/chell_texture/chell_point_right_sprite.h"

ChellPointRightSprite::ChellPointRightSprite() {}
ChellPointRightSprite::~ChellPointRightSprite() = default;

/*
Devuelve sprite de Chell apuntando a derecha.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellPointRightSprite::point_right(){
    return std::move(DynamicSprite({{1,2977}},188,225));
}

/*
Devuelve sprite de Chell apuntando ariba.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellPointRightSprite::point_up(){
    return std::move(DynamicSprite({{190,2977}},188,225));
}

/*
Devuelve sprite de Chell apuntando arriba y a derecha.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellPointRightSprite::point_right_up(){
    return std::move(DynamicSprite({{568,2977}},188,225));
}

/*
Devuelve sprite de Chell apuntando abajo.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellPointRightSprite::point_down(){
    return std::move(DynamicSprite({{213,2747}},170,200));
}

/*
Devuelve sprite de Chell apuntando abajo y a derecha.
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellPointRightSprite::point_right_down(){
    return std::move(DynamicSprite({{1,249}},164,199));
}
