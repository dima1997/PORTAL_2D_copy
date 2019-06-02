#ifndef TRIANGLE_BOTOM_RIGHT_TEXTURE_H
#define TRIANGLE_BOTOM_RIGHT_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class TriangleBotomRightTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la 
    imagen ALL_TRIANGLES_SPRITE; y el area del mapa de juego 
    que representa esta textura.
    POST: Inicializa una textura de triangulo de la esquina 
    inferior derecha.
    */
    TriangleBotomRightTexture(BigTexture & bigTexture, Area areaMap);

    /*
    Destruye la textura del triangulo de la esquina 
    inferior derecha.
    */
    virtual ~TriangleBotomRightTexture();
};

#endif // TRIANGLE_BOTOM_RIGHT_TEXTURE_H
