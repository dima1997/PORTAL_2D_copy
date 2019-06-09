#include "../../../includes/textures/rock_texture/rock_one_texture.h"

#include "../../../includes/textures/rock_texture/rock_one_sprite.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"

#include <memory>

/*
PRE: Recibe una gran textura que contiene de la imagen 
ROCKS_AND_BALLS_SPRITE de images_paths.h; y el area del 
mapa de juego que representa esta textura.
POST: Inicializa una textura de roca de tipo 1.
*/
RockOneTexture::RockOneTexture(BigTexture & bigTexture, Area areaMap)
:   Texture(bigTexture, 
            areaMap, 
            RockOneSprite::get_sprite()
    ) {}
/*
:    Texture(bigTexture, areaMap, 
        std::move(
            std::unique_ptr<SpriteStrategy>(new SpriteStrategy(
                std::move(std::unique_ptr<DynamicSprite>(
                    new RockOneSprite()
                ))
            ))
        )
    ) {}
*/

/*Destruye la textura de la roca de tipo 1.*/
RockOneTexture::~RockOneTexture() = default;
