#include "../../../includes/textures/door_texture/door_one_texure.h"

#include "../../../includes/textures/door_texture/door_one_sprite_strategy.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"

#include <memory>

/*
PRE: Recibe una gran textura que contiene de la imagen ALL_DOORS_SPRITES 
de images_paths.h; y el area del mapa de juego que representa esta 
textura.
POST: Inicializa una texture de bloque de metal.
*/
DoorOneTexture::DoorOneTexture(BigTexture & bigTexture, Area areaMap) 
:    Texture(bigTexture, areaMap, 
        std::move(
            std::unique_ptr<SpriteStrategy>(new DoorOneSpriteStrategy())
        )
    ) {}

/*Destruye la textura de la puerta con el numero 1.*/
DoorOneTexture::~DoorOneTexture() = default;