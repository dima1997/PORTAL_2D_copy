#include "../../../includes/textures/common_texture/null_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Iniciliza un sprite de nulo (sin imagen).
*/
NullSprite::NullSprite()
:   DynamicSprite(
        {
            {0,0}
        },
        0,0
    )
    {}
/*Destrue el sprite nulo.*/
NullSprite::~NullSprite() = default;
