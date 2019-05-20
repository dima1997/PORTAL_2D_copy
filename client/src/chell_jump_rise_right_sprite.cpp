#include "chell_jump_rise_right_sprite.h"

#include "dynamic_sprite.h"

/*
Inicializa un sprite dinamico de Chell saltando 
hacia la derecha.
Este sprite dinamico corresponde a una serie de sprites
de la imagen ALL_CHELL_SPRITES_PART_1, de images_path.h.
*/
ChellJumpRiseRightSprite::ChellJumpRiseRightSprite()
:   DynamicSprite(
        {
            {1,855},
            {145,855},
            {289,855},
            {433,855}
        },
        143, 228
    ) {}

/*
Destruye el sprite dinamico de Chell saltando 
hacia la derecha.
*/
ChellJumpRiseRightSprite::~ChellJumpRiseRightSprite() {}
