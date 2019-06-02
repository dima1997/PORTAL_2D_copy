#include "../../../includes/textures/button_texture/button_texture.h"

#include "../../../includes/textures/button_texture/button_sprite_strategy.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"

#include <memory>

/*
PRE: Recibe una gran textura que contiene de la imagen BUTTON_SPRITE 
de images_paths.h; y el area del mapa de juego que representa esta 
textura.
POST: Inicializa una textura de boton.
*/
ButtonTexture::ButtonTexture(BigTexture & bigTexture, Area areaMap) 
:    Texture(bigTexture, areaMap, 
        std::move(
            std::unique_ptr<SpriteStrategy>(new ButtonSpriteStrategy())
        )
    ) {}

/*Destruye la textura del boton.*/
ButtonTexture::~ButtonTexture() = default;
