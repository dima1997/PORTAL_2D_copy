#include "chell_running_sprite.h"

/*
Inicializa un sprite dinamico de Chell corriendo.
Este sprite dinamico corresponde a un series de sprites
de la imagen ALL_CHELL_SPRITES, de images_path.h.
*/
ChellRunningSprite::ChellRunningSprite()
:   DynamicSprite(
        {
            std::pair<int,int>(1,4123),
            std::pair<int,int>(196,4123),
            std::pair<int,int>(391,4123),
            std::pair<int,int>(586,4123),
            std::pair<int,int>(781,4123),
            std::pair<int,int>(976,4123),
            std::pair<int,int>(1171,4123),
            std::pair<int,int>(1366,4123),
            std::pair<int,int>(1,4328),
            std::pair<int,int>(196,4328),
            std::pair<int,int>(391,4328),
            std::pair<int,int>(586,4328),
        },
        194, 204
    ) {}

/*Destruye el sprite dinamico de chell corriendo*/
ChellRunningSprite::~ChellRunningSprite(){}

