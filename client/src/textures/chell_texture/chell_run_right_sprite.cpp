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
            {1,4123},
            {196,4123},
            {391,4123},
            {586,4123},
            {781,4123},
            {976,4123},
            {1171,4123},
            {1366,4123},
            {1,4328},
            {196,4328},
            {391,4328},
            {586,4328},
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
                {1,4123},
                {196,4123},
                {391,4123},
                {586,4123},
                {781,4123},
                {976,4123},
                {1171,4123},
                {1366,4123},
                {1,4328},
                {196,4328},
                {391,4328},
                {586,4328},
            },
            194, 204
        )
    );
} 