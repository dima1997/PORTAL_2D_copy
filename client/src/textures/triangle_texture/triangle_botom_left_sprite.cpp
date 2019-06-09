#include "../../../includes/textures/triangle_texture/triangle_botom_left_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Iniciliza un sprite de triangulo en la esquina 
inferior izquierda, que se encuentra en la 
imagen ALL_TRIANGLES_SPRITES de images_paths.h .
*/
TriangleBotomLeftSprite::TriangleBotomLeftSprite()
:   DynamicSprite(
        {
            {3,217}
        },
        190,180
    )
    {}
/*
Destruye el sprite del triangulo en la 
esquina inferior izquierda.
*/
TriangleBotomLeftSprite::~TriangleBotomLeftSprite() = default;

DynamicSprite TriangleBotomLeftSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {3,217}
            },
            190,180
        )
    );
} 
