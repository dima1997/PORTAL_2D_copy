#include "../../../includes/textures/block_metal_texture/block_metal_sprite_strategy.h"

#include "../../../includes/textures/block_metal_texture/block_metal_sprite.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"
#include <memory>

/*
Iniciliza un bloque sprite strategy, cuyos sprites 
se encuentran en la imagen ALL_BLOCKS de 
images_paths.h .
*/
BlockMetalSpriteStrategy::BlockMetalSpriteStrategy() 
:   SpriteStrategy(
        std::move(
            std::unique_ptr<DynamicSprite>(new BlockMetalSprite())
        )    
    ) {}

/*Destruye uel sprite strategy del bloque de metal.*/
BlockMetalSpriteStrategy::~BlockMetalSpriteStrategy() = default;
