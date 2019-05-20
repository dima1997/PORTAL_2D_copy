#include "chell_sweat_right_sprite.h"

#include "../../common_texture/dynamic_sprite.h"

/*
Inicializa un sprite dinamico de Chell sudando 
(mirando hacia la derecha).
Este sprite dinamico corresponde a una serie de sprites
de la imagen ALL_CHELL_SPRITES_PART_1, de images_path.h.
*/
ChellSweatRightSprite::ChellSweatRightSprite()
:   DynamicSprite(
        {
            {1,4993},
            {217,4993},
            {433,4993},
            {649,4993},
            {865,4993},
            {1081,4993},
            {1297,4993},
            {1,5219},
            {217,5219},
            {433,5219},
            {649,5219},
            {865,5219},
            {1081,5219},
        },
        215, 225
    ) {}

/*
Destruye el sprite dinamico de chell sudando
(mirando hacia la derecha).
*/
ChellSweatRightSprite::~ChellSweatRightSprite() {}
