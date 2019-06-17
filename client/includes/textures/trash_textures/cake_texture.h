#ifndef CAKE_TEXTURE_H
#define CAKE_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class CakeTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la 
    imagen CAKE_SPRITES; y el area del mapa de juego 
    que representa esta textura.
    POST: Inicializa una textura de torta.
    */
    CakeTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura del bloque de torta.*/
    virtual ~CakeTexture();
};

#endif // CAKE_TEXTURE_H
