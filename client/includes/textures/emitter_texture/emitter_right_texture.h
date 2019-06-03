#ifndef EMITTER_RIGHT_TEXTURE_H
#define EMITTER_RIGHT_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class EmitterRightTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la 
    imagen ALL_BLOCKS_SPRTES; y el area del mapa de juego 
    que representa esta textura.
    POST: Inicializa una textura de bloque emisor a derecha.
    */
    EmitterRightTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura del bloque emisor a derecha.*/
    virtual ~EmitterRightTexture();
};

#endif // EMITTER_RIGHT_TEXTURE_H
