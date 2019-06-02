#include "../../../includes/textures/triangle_texture/triangle_top_right_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Iniciliza un sprite de triangulo en la esquina 
superior derecha, que se encuentra en la 
imagen ALL_TRIANGLES_SPRITES de images_paths.h .
*/
TriangleTopRightSprite::TriangleTopRightSprite()
:   DynamicSprite(
        {
            {202,29}
        },
        180,190
    )
    {}
/*
Destruye el sprite del triangulo en la 
esquina inferior izquierda.
*/
TriangleTopRightSprite::~TriangleTopRightSprite() = default;
