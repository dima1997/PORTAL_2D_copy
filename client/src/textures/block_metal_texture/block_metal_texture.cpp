#include "../../../includes/textures/block_metal_texture/block_metal_texture.h"

#include "../../../includes/textures/block_metal_texture/block_metal_sprite.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"

#include <memory>

/*
PRE: Recibe una gran textura que contiene de la imagen ALL_BLOCKS 
de images_paths.h; y el area del mapa de juego que representa esta 
textura.
POST: Inicializa una texture de bloque de metal.
*/
BlockMetalTexture::BlockMetalTexture(BigTexture & bigTexture, Area areaMap)
:   Texture(bigTexture, 
            areaMap, 
            BlockMetalSprite::get_sprite()
    ) {}

/*Destruye la textura del bloque de metal.*/
BlockMetalTexture::~BlockMetalTexture() = default;
