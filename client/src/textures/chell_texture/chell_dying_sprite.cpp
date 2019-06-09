#include "../../../includes/textures/chell_texture/chell_dying_sprite.h"

/*
Inicializa un sprite dinamico de Chell mueriendo.
Este sprite dinamico corresponde a una serie de 
sprites de la imagen ALL_CHELL_SPRITES, de 
images_path.h.
*/
ChellDyingSprite::ChellDyingSprite()
:   DynamicSprite(
        {
            {,}
        },
        , 
    ) {}

/*
Destruye el sprite dinamico de chell muriendo 
hacia la derecha.
*/
ChellDyingSprite::~ChellDyingSprite() = default;

