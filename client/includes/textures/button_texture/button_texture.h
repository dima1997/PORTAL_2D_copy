#ifndef BUTTON_TEXTURE_H
#define BUTTON_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class ButtonTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la 
    imagen BUTTON_SPRITE; y el area del mapa de juego 
    que representa esta textura.
    POST: Inicializa una textura de boton.
    */
    ButtonTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura del boton.*/
    virtual ~ButtonTexture();
};

#endif // BUTTON_TEXTURE_H
