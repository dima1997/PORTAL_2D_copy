#ifndef ENERGY_BALL_TEXTURE_H
#define ENERGY_BALL_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class EnergyBallTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la imagen 
    ENERGY_BALLS_SPRITES de images_path.h; y el area
    del mapa de juego que representa esta textura.
    POST: Inicializa una texture de una bola de energia.
    */
    EnergyBallTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura de la bola de energia.*/
    virtual ~EnergyBallTexture();
};

#endif // ENERGY_BALL_TEXTURE_H
