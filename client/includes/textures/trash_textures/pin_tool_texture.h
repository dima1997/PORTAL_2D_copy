#ifndef PIN_TOOL_TEXTURE_H
#define PIN_TOOL_TEXTURE_H

#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"

class PinToolTexture : public Texture {
public:
    PinToolTexture(BigTexture & bigTexture, Area areaMap);
    virtual ~PinToolTexture();
};

#endif // PIN_TOOL_TEXTURE_H
