#include "../../../includes/textures/triangle_texture/triangle_botom_right_texture.h"

#include "../../../includes/textures/triangle_texture/triangle_botom_right_sprite.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"

#include <memory>

/*
PRE: Recibe una gran textura que contiene de la imagen 
ALL_TRIANGLES_SPRITES de images_paths.h; y el area del 
mapa de juego que representa esta textura.
POST: Inicializa una textura de triangulo en la 
esquina inferior derecha.
*/
TriangleBotomRightTexture::TriangleBotomRightTexture(BigTexture & bigTexture, Area areaMap) 
:    Texture(bigTexture, areaMap, 
        std::move(
            std::unique_ptr<SpriteStrategy>(new SpriteStrategy(
                std::move(std::unique_ptr<DynamicSprite>(
                    new TriangleBotomRightSprite()
                ))
            ))
        )
    ) {}

/*
Destruye la textura del triangulo en la 
esquina inferior derecha.
*/
TriangleBotomRightTexture::~TriangleBotomRightTexture() = default;
