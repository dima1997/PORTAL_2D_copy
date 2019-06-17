#ifndef RECORD_TEXTURE_H
#define RECORD_TEXTURE_H

#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"

#include <memory>

class RecordTexture : public Texture {
protected:
    /*
    Devuelve el area de destino de la textura de grabacion de forma 
    que quede siempre el la esquina superior izquierda de la ventana
    */
    Area getAreaDest(float adjuster, const Area & areaCamera);
    
public:
    RecordTexture(BigTexture & bigTexture, Area areaMap);
    virtual ~RecordTexture();
};

#endif // RECORD_TEXTURE_H
