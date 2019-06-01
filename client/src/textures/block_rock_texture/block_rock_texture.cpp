#include "../../../includes/textures/block_rock_texture/block_rock_texture.h"

#include "../../../includes/textures/block_rock_texture/block_rock_sprite.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"

#include <memory>

/*
PRE: Recibe una gran textura que contiene de la imagen ALL_BLOCKS 
de images_paths.h; y el area del mapa de juego que representa esta 
textura.
POST: Inicializa una texture de bloque de piedra.
*/
BlockRockTexture::BlockRockTexture(BigTexture & bigTexture, Area areaMap) 
:    Texture(bigTexture, areaMap, 
        std::move(
            std::unique_ptr<SpriteStrategy>(new SpriteStrategy(
                std::move(std::unique_ptr<DynamicSprite>(
                    new BlockRockSprite()
                ))
            ))
        )
    ) {}

/*Destruye la textura del bloque de piedra.*/
BlockRockTexture::~BlockRockTexture() = default;
