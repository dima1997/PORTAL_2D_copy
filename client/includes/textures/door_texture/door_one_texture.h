#ifndef DOOR_ONE_TEXTURE_H
#define DOOR_ONE_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class DoorOneTexture : public Texture{
public:
    /*
    PRE: Recibe una gran textura que contiene de la imagen ALL_DOORS_SPRITES 
    de images_paths.h; y el area del mapa de juego que representa esta 
    textura.
    POST: Inicializa una texture de bloque de metal.
    */
    DoorOneTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura de puerta con el numero 1.*/
    virtual ~DoorOneTexture();
};

#endif // DOOR_ONE_TEXTURE_H
