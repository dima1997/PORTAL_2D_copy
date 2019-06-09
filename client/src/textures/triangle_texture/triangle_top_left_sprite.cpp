#include "../../../includes/textures/triangle_texture/triangle_top_left_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Iniciliza un sprite de triangulo en la esquina 
superior izquierda, que se encuentra en la 
imagen ALL_TRIANGLES_SPRITES de images_paths.h .
*/
TriangleTopLeftSprite::TriangleTopLeftSprite()
:   DynamicSprite(
        {
            {3,29}
        },
        180,190
    )
    {}
/*
Destruye el sprite del triangulo en la 
esquina superior izquierda.
*/
TriangleTopLeftSprite::~TriangleTopLeftSprite() = default;

DynamicSprite TriangleTopLeftSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {3,29}
            },
            180,190
        )
    );
} 
