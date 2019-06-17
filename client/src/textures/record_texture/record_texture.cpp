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
            )))
    ){}

RecordTexture::~RecordTexture() = default;

/*
Devuelve el area de destino de la textura de grabacion de forma 
que quede siempre el la esquina superior izquierda de la ventana
*/
Area RecordTexture::getAreaDest(float adjuster, const Area & areaCamera) {
    Area areaCameraTopLeft = areaCamera.from_center_to_top_left(); 
    this->areaMap.setX(areaCameraTopLeft.getX());
    this->areaMap.setY(areaCameraTopLeft.getY());
    Area dest = this->areaMap.from_center_to_top_left();
    dest = dest.adjust(adjuster);
    return std::move(dest);
}
