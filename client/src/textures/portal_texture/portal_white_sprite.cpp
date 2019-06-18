#include "../../../includes/textures/portal_texture/portal_white_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

PortalWhiteSprite::PortalWhiteSprite() {}
PortalWhiteSprite::~PortalWhiteSprite() = default;

/*
Devuelve un sprite dinamico de portal blanco.
IMAGE_PATH : PORTAL_SPRITES
*/
DynamicSprite PortalWhiteSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {0,0},
                {220,0},
                {440,0},
                {666,0},
            },
            220,450
        ) 
    );
} 