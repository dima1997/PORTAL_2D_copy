#ifndef BLOCK_ROCK_TEXTURE_H
#define BLOCK_ROCK_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class BlockRockTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la 
    imagen ALL_BLOCKS_SPRTES; y el area del mapa de juego 
    que representa esta textura.
    POST: Inicializa una textura de bloque de piedra.
    */
    BlockRockTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura del bloque de piedra.*/
    virtual ~BlockRockTexture();
};

#endif // BLOCK_ROCK_TEXTURE_H
