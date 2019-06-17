#ifndef BLOCK_ACID_TEXTURE_H
#define BLOCK_ACID_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class BlockAcidTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la 
    imagen ALL_BLOCKS_SPRTES; y el area del mapa de juego 
    que representa esta textura.
    POST: Inicializa una textura de bloque de acido.
    */
    BlockAcidTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura del bloque de acido.*/
    virtual ~BlockAcidTexture();
};

#endif // BLOCK_ACID_TEXTURE_H
