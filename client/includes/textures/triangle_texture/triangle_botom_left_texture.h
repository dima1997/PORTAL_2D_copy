#ifndef TRIANGLE_BOTON_LEFT_TEXTURE_H
#define TRIANGLE_BOTON_LEFT_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class TriangleBotomLeftTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la 
    imagen ALL_TRIANGLES_SPRITE; y el area del mapa de juego 
    que representa esta textura.
    POST: Inicializa una textura de bloque de piedra.
    */
    TriangleBotomLeftTexture(BigTexture & bigTexture, Area areaMap);

    /*
    Destruye la textura del triangulo de la esquina 
    inferior izquierda.
    */
    virtual ~TriangleBotomLeftTexture();
};

#endif // TRIANGLE_BOTON_LEFT_TEXTURE_H
