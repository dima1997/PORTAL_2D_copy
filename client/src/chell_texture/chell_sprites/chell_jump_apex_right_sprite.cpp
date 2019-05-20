#include "chell_jump_apex_right_sprite.h"

#include "../../common_texture/dynamic_sprite.h"

/*
Inicializa un sprite dinamico de Chell saltando 
verticalemente (mirando hacia la derecha).
Este sprite dinamico corresponde a una serie de sprites
de la imagen ALL_CHELL_SPRITES_PART_1, de images_path.h.
*/
ChellJumpApexRightSprite::ChellJumpApexRightSprite()
:   DynamicSprite(
        {
            {1,21}
        },
        137, 207
    ) {}

/*
Destruye el sprite dinamico de Chell saltando 
verticalemente (mirando hacia la derecha).
*/
ChellJumpApexRightSprite::~ChellJumpApexRightSprite() {}