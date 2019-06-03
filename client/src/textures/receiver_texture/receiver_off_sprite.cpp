#include "../../../includes/textures/receiver_texture/receiver_off_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Inicializa un sprite de bloque recibidor de bolas de energia 
bloqueado que se encuentra en la imagen ALL_BLOCKS_SPRITES de 
images_paths.h .
*/
ReceiverOffSprite::ReceiverOffSprite()
:   DynamicSprite(
        {
            {1,2538}
        },
        200,197
    )
    {}

/*
Destruye el sprite de bloque recibidor de bolas de 
energia bloqueado.
*/
ReceiverOffSprite::~ReceiverOffSprite() = default;
