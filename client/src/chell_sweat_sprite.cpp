#include "chell_sweat_sprite.h"

/*
Inicializa un sprite dinamico de Chell sudando.
Este sprite dinamico corresponde a un series de sprites
de la imagen ALL_CHELL_SPRITES, de images_path.h.
*/
ChellSweatSprite::ChellSweatSprite()
:   DynamicSprite(
        {
            std::pair<int,int>(1,4993),
            std::pair<int,int>(217,4993),
            std::pair<int,int>(433,4993),
            std::pair<int,int>(649,4993),
            std::pair<int,int>(865,4993),
            std::pair<int,int>(1081,4993),
            std::pair<int,int>(1297,4993),
            std::pair<int,int>(1,5219),
            std::pair<int,int>(217,5219),
            std::pair<int,int>(433,5219),
            std::pair<int,int>(649,5219),
            std::pair<int,int>(865,5219),
            std::pair<int,int>(1081,5219),
        },
        215, 225
    ) {}

/*Destruye el sprite dinamico de chell sudando*/
ChellSweatSprite::~ChellSweatSprite() {}
