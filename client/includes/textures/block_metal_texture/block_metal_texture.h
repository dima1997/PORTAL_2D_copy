#ifndef BLOCK_METAL_TEXTURE_H
#define BLOCK_METAL_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class BlockMetalTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la imagen all_blocks.png; y el area
    del mapa de juego que representa esta textura.
    POST: Inicializa una texture de bloque de metal.s
    */
    BlockMetalTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura del bloque de metal.*/
    virtual ~BlockMetalTexture();
};

#endif // BLOCK_METAL_TEXTURE_H
