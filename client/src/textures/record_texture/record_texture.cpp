#include "../../../includes/textures/record_texture/record_texture.h"
#include "../../../includes/textures/record_texture/recording_sprite.h"

#include "../../../includes/textures/common_texture/null_sprite.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/two_sprites_strategy.h" 

#include <memory>

RecordTexture::RecordTexture(BigTexture & bigTexture, Area areaMap)
:   Texture(bigTexture, 
            areaMap, 
            std::move(std::unique_ptr<SpriteStrategy>(new TwoSpritesStrategy(
                NullSprite::get_sprite(),
                RecordingSprite::get_sprite()
            ))),
            0,
            255,
            255,
            255
    ){}

RecordTexture::~RecordTexture() = default;

/*
Renderiza la textura de grabacion de forma 
que quede siempre en la esquina superior 
izquierda de la ventana.
*/
void RecordTexture::render(float adjuster, const Area & areaCamera) {
    Area src = (*this->ptrSpriteStrategy).getNextArea();
    Area dest = this->areaMap.adjust(adjuster);
    dest.setX(0);
    dest.setY(0);
    this->bigTexture.render(src, dest, NO_FLIP);
}