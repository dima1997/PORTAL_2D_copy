#include "../../../includes/textures/chell_texture/chell_run_right_sprite.h"

/*
Inicializa un sprite dinamico de Chell corriendo 
hacia la derecha.
Este sprite dinamico corresponde a una serie de 
sprites de la imagen ALL_CHELL_SPRITES, de 
images_path.h.
*/
ChellRunRightSprite::ChellRunRightSprite()
:   DynamicSprite(
        {
            {1,2542},
            {196,2542},
            {391,2542},
            {586,2542},
            {781,2542},
            {976,2542},
            {1171,2542},
            {1366,2542},
            {1,2747},
            {196,2747},
            {391,2747},
            {586,2747}
        },
        194, 204
    ) {}

/*
Destruye el sprite dinamico de chell corriendo 
hacia la derecha.
*/
ChellRunRightSprite::~ChellRunRightSprite(){}

DynamicSprite ChellRunRightSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {1,2542},
                {196,2542},
                {391,2542},
                {586,2542},
                {781,2542},
                {976,2542},
                {1171,2542},
                {1366,2542},
                {1,2747},
                {196,2747},
                {391,2747},
                {586,2747}
            },
            194, 204
        )
    );
} 