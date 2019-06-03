#include "../../../includes/textures/cake_texture/cake_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Inicializa un sprite de bloque de torta que se 
encuentra en la imagen CAKE_SPRITES de images_paths.h .
*/
CakeSprite::CakeSprite()
:   DynamicSprite(
        {
            {6,6},
            {92,6},
            {179,6},
            {275,6},
            {362,6},
            {448,6},
            {534,6},
            {620,6}
        },
        84,78
    )
    {}
/*Destruye el sprite de bloque de torta.*/
CakeSprite::~CakeSprite() = default;
