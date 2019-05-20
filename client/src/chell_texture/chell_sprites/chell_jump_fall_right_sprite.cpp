#include "chell_jump_fall_right_sprite.h"

#include "../../common_texture/dynamic_sprite.h"

/*
Inicializa un sprite dinamico de Chell cayendo
hacia la derecha (tras haber saltado).
Este sprite dinamico corresponde a una serie de sprites
de la imagen ALL_CHELL_SPRITES_PART_1, de images_path.h.
*/
ChellJumpFallRightSprite::ChellJumpFallRightSprite()
:   DynamicSprite(
        {
            {1,1835},
            {158,1835},
            {315,1835},
            {472,1835}
            
        },
        156, 217
    ) {}

/*
Destruye el sprite dinamico de Chell cayendo 
hacia la derecha (tras haber saltado).
*/
ChellJumpFallRightSprite::~ChellJumpFallRightSprite() {}