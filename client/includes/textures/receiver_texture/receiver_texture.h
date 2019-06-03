#ifndef RECEIVER_TEXTURE_H
#define RECEIVER_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class ReceiverTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la imagen 
    ALL_BLOCKS_SPRITES de images_path.h; y el area
    del mapa de juego que representa esta textura.
    POST: Inicializa una texture de recibidor.
    */
    ReceiverTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura del recibidor.*/
    virtual ~ReceiverTexture();
};

#endif // RECEIVER_TEXTURE_H
