#ifndef PORTAL_BLUE_TEXTURE_H
#define PORTAL_BLUE_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class PortalBlueTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la imagen 
    PORTAL_SPRITE de images_path.h; y el area
    del mapa de juego que representa esta textura.
    POST: Inicializa una texture de portal azul.
    */
    PortalBlueTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura del portal azul.*/
    virtual ~PortalBlueTexture();
};

#endif // PORTAL_BLUE_TEXTURE_H
