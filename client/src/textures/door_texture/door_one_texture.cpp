#include "../../../includes/textures/door_texture/door_one_texture.h"

#include "../../../includes/textures/door_texture/door_one_closed_sprite.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"

#include <memory>

/*
PRE: Recibe una gran textura que contiene de la imagen ALL_DOORS_SPRITES 
de images_paths.h; y el area del mapa de juego que representa esta 
textura.
POST: Inicializa una textura de puerta con numero 1.
*/
DoorOneTexture::DoorOneTexture(BigTexture & bigTexture, Area areaMap) 
:   Texture(bigTexture, 
            areaMap, 
            DoorOneClosedSprite::get_sprite()

    ) {}
/*
:   Texture(bigTexture, areaMap, 
        std::move(
            std::unique_ptr<SpriteStrategy>(new SpriteStrategy(
                std::move(std::unique_ptr<DynamicSprite>(
                    new DoorOneClosedSprite()
                ))
            ))
        )
    ) {}
*/

/*Destruye la textura de la puerta con el numero 1.*/
DoorOneTexture::~DoorOneTexture() = default;
