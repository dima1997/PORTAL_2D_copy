#include "../../../includes/textures/portal_texture/portal_blue_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Iniciliza un sprite de portal azul que se 
encuentra en la imagen PORTAL_BLUE_SPRITES.png .
*/
PortalBlueSprite::PortalBlueSprite()
:   DynamicSprite(
        {
            {0,0},
            {220,0},
            {440,0},
            {660,0},
        },
        220,450
    )
    {}
/*Destrue el sprite de portal azul.*/
PortalBlueSprite::~PortalBlueSprite() = default;
