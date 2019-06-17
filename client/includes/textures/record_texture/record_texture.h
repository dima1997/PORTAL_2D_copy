#ifndef RECORD_TEXTURE_H
#define RECORD_TEXTURE_H

#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"

#include <memory>

class RecordTexture : public Texture {
public:
    RecordTexture(BigTexture & bigTexture, Area areaMap);
    virtual ~RecordTexture();
    
    /*
    Renderiza la textura de grabacion de forma 
    que quede siempre en la esquina superior 
    izquierda de la ventana.
    */
    virtual void render(float adjuster, const Area & areaCamera);
};

#endif // RECORD_TEXTURE_H
