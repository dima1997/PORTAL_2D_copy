#ifndef LOADING_TEXTURE_H
#define LOADING_TEXTURE_H

#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"

class LoadingTexture : public Texture {
public:
    LoadingTexture(BigTexture & bigTexture, Area & areaMap);
    virtual ~LoadingTexture();
    
    /*
    Renderiza la textura de partida cargando de 
    forma que ocupe toda la pantalla.
    */
    virtual void render(float adjuster, const Area & areaCamera);
};

#endif // LOADING_TEXTURE_H
