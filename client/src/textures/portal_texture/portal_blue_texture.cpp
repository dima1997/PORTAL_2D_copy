#include "../../../includes/textures/portal_texture/portal_blue_texture.h"

#include "../../../includes/textures/portal_texture/portal_sprite_strategy.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"

#include <memory>

/*
PRE: Recibe una gran textura que contiene de la imagen PORTAL_SPRITES 
de images_paths.h; y el area del mapa de juego que representa esta 
textura.
POST: Inicializa una texture de portal azul.
*/
PortalBlueTexture::PortalBlueTexture(BigTexture & bigTexture, Area areaMap) 
:    Texture(bigTexture, areaMap, 
        std::move(
            std::unique_ptr<SpriteStrategy>(new PortalSpriteStrategy())
        )
    ) {}

/*Destruye la textura del portal azul.*/
PortalBlueTexture::~PortalBlueTexture() = default;
