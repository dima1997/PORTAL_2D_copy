#ifndef ROCK_ONE_TEXTURE_H
#define ROCK_ONE_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class RockOneTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la 
    imagen ROCKS_AND_BALL_SPRITES; y el area del mapa de juego 
    que representa esta textura.
    POST: Inicializa una textura de roca.
    */
    RockOneTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura de la roca.*/
    virtual ~RockOneTexture();
};

#endif // ROCK_ONE_TEXTURE_H
