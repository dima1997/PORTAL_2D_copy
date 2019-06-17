#include "../../../includes/textures/pin_tool_texture/pin_tool_texture.h"

#include "../../../includes/textures/pin_tool_texture/pin_tool_sprite_strategy.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"

#include <memory>

PinToolTexture::PinToolTexture(BigTexture & bigTexture, Area areaMap)
:   Texture(
        bigTexture,
        areaMap,
        std::move(std::unique_ptr<SpriteStrategy>(new PinToolSpriteStrategy()))
    )
    {}

PinToolTexture::~PinToolTexture() = default;

