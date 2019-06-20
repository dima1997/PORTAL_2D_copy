#ifndef PORTAL_TEXTURE_H
#define PORTAL_TEXTURE_H

#include "portal_sprite_strategy.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"
#include "../common_texture/texture.h"

class PortalTexture : public Texture {
public:
    PortalTexture(
        BigTexture & bigTexture, 
        Area & areaMap, 
        uint8_t redMod, 
        uint8_t greenMod, 
        uint8_t blueMod
    );
    virtual ~PortalTexture();
    /*
    PRE: Recibe unas coordenadas x,y del vertice 
    de la normal de portal respecto de su centro 
    de coordenadas.
    POST: Orienta al portal segun su nueva normal.
    */
    virtual void point_to(float x, float y);
};

#endif // PORTAL_TEXTURE_H
