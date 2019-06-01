#ifndef DOOR_THREE_TEXTURE_H
#define DOOR_THREE_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class DoorThreeTexture : public Texture{
public:
    /*
    PRE: Recibe una gran textura que contiene de la imagen ALL_DOORS_SPRITES 
    de images_paths.h; y el area del mapa de juego que representa esta 
    textura.
    POST: Inicializa una textura de puerta con numero 3.
    */
    DoorThreeTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura de puerta con el numero 3.*/
    virtual ~DoorThreeTexture();
};

#endif // DOOR_THREE_TEXTURE_H
