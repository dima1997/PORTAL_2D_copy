#include "../../../includes/textures/portal_texture/portal_texture.h"

#include "../../../includes/textures/portal_texture/portal_sprite_strategy.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/area.h"

PortalTexture::PortalTexture(
    BigTexture & bigTexture, 
    Area & areaMap, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
:   Texture(
        bigTexture,
        areaMap,
        std::move(std::unique_ptr<SpriteStrategy>(
            new PortalSpriteStrategy()
        )),
        0,
        redMod,
        greenMod,
        blueMod
    ) {}

PortalTexture::~PortalTexture() = default;

/*
PRE: Recibe unas coordenadas x,y del vertice 
de la normal de portal respecto de su centro 
de coordenadas.
POST: Orienta al portal segun su nueva normal.
*/
void PortalTexture::point_to(float x, float y){
    if (x == 0 && y != 0){
        this->angle = 0;
        return;
    }

    if (x != 0 && y == 0){
        this->angle = 90;
        return;
    }

    if ( (x < 0 && y < 0) || (x > 0 && y > 0) ){
        this->angle = 45;
        return;
    }

    if ( (x < 0 && y > 0) || (x < 0 && y > 0) ){
        this->angle = 315;
        return;
    }
}
