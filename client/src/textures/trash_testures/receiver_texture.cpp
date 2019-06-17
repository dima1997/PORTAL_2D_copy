#include "../../../includes/textures/receiver_texture/receiver_texture.h"

#include "../../../includes/textures/receiver_texture/receiver_sprite_strategy.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"

#include <memory>

/*
PRE: Recibe una gran textura que contiene de la imagen ALL_BLOCKS_SPRITES 
de images_paths.h; y el area del mapa de juego que representa esta 
textura.
POST: Inicializa una texture de un bloque recibidor de bolas de energia.
*/
ReceiverTexture::ReceiverTexture(BigTexture & bigTexture, Area areaMap) 
:    Texture(bigTexture, areaMap, 
        std::move(
            std::unique_ptr<SpriteStrategy>(
                new ReceiverSpriteStrategy()   
            )
        )
    ) {}

/*Destruye la textura del bloque recibir de bolas de energia.*/
ReceiverTexture::~ReceiverTexture() = default;
