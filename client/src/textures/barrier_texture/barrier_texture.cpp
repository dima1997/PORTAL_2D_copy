#include "../../../includes/textures/barrier_texture/barrier_texture.h"

#include "../../../includes/textures/barrier_texture/barrier_sprite.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"

#include <memory>

/*
PRE: Recibe una gran textura que contiene de la imagen 
BARRIER_SPRITE de images_paths.h; y el area del 
mapa de juego que representa esta textura.
POST: Inicializa una textura de barrera.
*/
BarrierTexture::BarrierTexture(BigTexture & bigTexture, Area areaMap) 
:   Texture(bigTexture, 
            areaMap, 
            BarrierSprite::get_sprite()
    ) {}

/*Destruye la textura de barrera.*/
BarrierTexture::~BarrierTexture() = default;
