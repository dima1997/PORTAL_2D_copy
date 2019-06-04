#include "../../../includes/textures/background_texture/background_one_texture.h"

#include "../../../includes/textures/background_texture/background_one_sprite.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"

#include <memory>

/*
PRE: Recibe una gran textura que contiene de la imagen 
BACKGROUND de images_paths.h; y el area del 
mapa de juego que representa esta textura.
POST: Inicializa una textura de fondo 1.
*/
BackgroundOneTexture::BackgroundOneTexture(BigTexture & bigTexture, Area areaMap) 
:    Texture(bigTexture, areaMap, 
        std::move(
            std::unique_ptr<SpriteStrategy>(new SpriteStrategy(
                std::move(std::unique_ptr<DynamicSprite>(
                    new BackgroundOneSprite()
                ))
            ))
        )
    ) {}

/*Destruye la textura de fondo 1.*/
BackgroundOneTexture::~BackgroundOneTexture() = default;
