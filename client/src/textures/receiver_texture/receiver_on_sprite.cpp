#include "../../../includes/textures/receiver_texture/receiver_on_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Inicializa un sprite de bloque recibidor de bolas de energia 
desbloqueado que se encuentra en la imagen ALL_BLOCKS_SPRITES de 
images_paths.h .
*/
ReceiverOnSprite::ReceiverOnSprite()
:   DynamicSprite(
        {
            {1006,2538}
        },
        200,197
    )
    {}

/*
Destruye el sprite de bloque recibidor de bolas de 
energia desbloqueado.
*/
ReceiverOnSprite::~ReceiverOnSprite() = default;

DynamicSprite ReceiverOnSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {1006,2538}
            },
            200,197
        ) 
    );
} 