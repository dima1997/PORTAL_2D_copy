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
    float xNow = this->areaMap.getX();
    float yNow = this->areaMap.getY();
    if (xNow == x){
        if (yNow != y){
            this->angle = 0;
            return;
        }
        return;
    }
    if (yNow == y){
        if (xNow != x){
            this->angle = 90;
            return;
        }
        return;
    }
    if (((yNow < y) && (xNow < x)) || ((yNow > y) && (xNow > x))){
        this->angle = 45;
        return;
    }
    if (((yNow > y) && (xNow < x)) || ((yNow < y) && (xNow > x))){
        this->angle = 315;
        return;
    }
}
