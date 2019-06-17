#include "../../../includes/textures/energy_ball_texture/energy_ball_texture.h"

#include "../../../includes/textures/energy_ball_texture/energy_ball_sprite_strategy.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"

#include <memory>

/*
PRE: Recibe una gran textura que contiene de la imagen 
ALL_ENERGY_BALLS_SPRITES de images_paths.h; y el area 
del mapa de juego que representa esta textura.
POST: Inicializa una textura de bola de energia.
*/
EnergyBallTexture::EnergyBallTexture(BigTexture & bigTexture, Area areaMap) 
:    Texture(bigTexture, areaMap, 
        std::move(
            std::unique_ptr<SpriteStrategy>(new EnergyBallSpriteStrategy())
        )
    ) {}

/*Destruye la textura de bola de energia.*/
EnergyBallTexture::~EnergyBallTexture() = default;