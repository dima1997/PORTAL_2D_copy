#include "../../../includes/textures/block_acid_texture/block_acid_texture.h"

#include "../../../includes/textures/block_acid_texture/block_acid_sprite.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"

#include <memory>

/*
PRE: Recibe una gran textura que contiene de la imagen ALL_BLOCKS_SPRITES 
de images_paths.h; y el area del mapa de juego que representa esta 
textura.
POST: Inicializa una texture de bloque de acido.
*/
BlockAcidTexture::BlockAcidTexture(BigTexture & bigTexture, Area areaMap) 
:    Texture(bigTexture, areaMap, 
        std::move(
            std::unique_ptr<SpriteStrategy>(new SpriteStrategy(
                std::move(std::unique_ptr<DynamicSprite>(
                    new BlockAcidSprite()
                ))
            ))
        )
    ) {}

/*Destruye la textura del bloque de acido.*/
BlockAcidTexture::~BlockAcidTexture() = default;
