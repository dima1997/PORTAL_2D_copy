#ifndef BARRIER_TEXTURE_H
#define BARRIER_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class BarrierTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la 
    imagen BARRIER_SPRITE; y el area del mapa de juego 
    que representa esta textura.
    POST: Inicializa una textura de barrera.
    */
    BarrierTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura de la roca.*/
    virtual ~BarrierTexture();
};

#endif // BARRIER_TEXTURE_H
