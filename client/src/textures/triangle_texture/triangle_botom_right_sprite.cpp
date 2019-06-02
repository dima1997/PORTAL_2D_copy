#include "../../../includes/textures/triangle_texture/triangle_botom_right_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Iniciliza un sprite de triangulo en la esquina 
inferior derecha, que se encuentra en la 
imagen ALL_TRIANGLES_SPRITES de images_paths.h .
*/
TriangleBotomRightSprite::TriangleBotomRightSprite()
:   DynamicSprite(
        {
            {197,217}
        },
        190,180
    )
    {}
/*
Destruye el sprite del triangulo en la 
esquina inferior derecha.
*/
TriangleBotomRightSprite::~TriangleBotomRightSprite() = default;
