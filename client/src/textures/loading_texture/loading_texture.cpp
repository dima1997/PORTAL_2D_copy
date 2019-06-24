#include "../../../includes/textures/loading_texture/loading_texture.h"
#include "../../../includes/textures/loading_texture/loading_sprite.h"

#include "../../../includes/textures/common_texture/null_sprite.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/two_sprites_strategy.h" 

#include <memory>

LoadingTexture::LoadingTexture(BigTexture & bigTexture, Area & areaMap)
:   Texture(bigTexture, 
            areaMap, 
            std::move(std::unique_ptr<SpriteStrategy>(new TwoSpritesStrategy(
                LoadingSprite::get_sprite(),
                NullSprite::get_sprite()
            ))),
            0,
            255,
            255,
            255
    ){}

LoadingTexture::~LoadingTexture() = default;

/*
Renderiza la textura de partida cargando de 
forma que ocupe toda la pantalla.
*/
void LoadingTexture::render(float adjuster, const Area & areaCamera) {
    Area src = (*this->ptrSpriteStrategy).getNextArea();
    Area dest = areaCamera.adjust(adjuster);
    dest.setX(0);
    dest.setY(0);
    this->bigTexture.render(src, dest, NO_FLIP);
}