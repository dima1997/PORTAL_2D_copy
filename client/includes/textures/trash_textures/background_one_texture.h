#ifndef BACKGROUND_ONE_TEXTURE_H
#define BACKGROUND_ONE_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class BackgroundOneTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la 
    imagen BACKGROUND; y el area del mapa de juego 
    que representa esta textura.
    POST: Inicializa una textura de fondo 1.
    */
    BackgroundOneTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura de fondo 1.*/
    virtual ~BackgroundOneTexture();
};

#endif // BACKGROUND_ONE_TEXTURE_H
