#ifndef TRIANGLE_TOP_LEFT_TEXTURE_H
#define TRIANGLE_TOP_LEFT_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class TriangleTopLeftTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la 
    imagen ALL_TRIANGLES_SPRITE; y el area del mapa de juego 
    que representa esta textura.
    POST: Inicializa una textura de triangulo en la esquina 
    superior izquierda.
    */
    TriangleTopLeftTexture(BigTexture & bigTexture, Area areaMap);

    /*
    Destruye la textura del triangulo de la esquina 
    superior izquierda.
    */
    virtual ~TriangleTopLeftTexture();
};

#endif // TRIANGLE_TOP_LEFT_TEXTURE_H
