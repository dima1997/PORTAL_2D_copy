#include "../../../includes/textures/receiver_texture/receiver_unlocking_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

/*
Inicializa un sprite de bloque recibidor de bolas de energia 
desbloqueado que se encuentra en la imagen ALL_BLOCKS_SPRITES de 
images_paths.h .
*/
ReceiverUnlockingSprite::ReceiverUnlockingSprite()
:   DynamicSprite(
        {
            {202,2538},
            {403,2538},
            {604,2538},
            {805,2538}
        },
        200,197
    )
    {}

/*
Destruye el sprite de bloque recibidor desbloqueadose.
*/
ReceiverUnlockingSprite::~ReceiverUnlockingSprite() = default;

DynamicSprite ReceiverUnlockingSprite::get_sprite(){
    return std::move(
        DynamicSprite(
            {
                {202,2538},
                {403,2538},
                {604,2538},
                {805,2538}
            },
            200,197
        )
    );
}