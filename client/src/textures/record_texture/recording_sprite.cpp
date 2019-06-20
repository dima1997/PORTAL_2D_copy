#include "../../../includes/textures/record_texture/recording_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

RecordingSprite::RecordingSprite(){}
RecordingSprite::~RecordingSprite() = default;

/*
Devuelve el sprite del video siendo grabado.
IMAGE_PATH : ALL_BLOCKS_SPRITES
*/
DynamicSprite RecordingSprite::get_sprite(){
    return std::move(DynamicSprite({{1009,18}},193,193));
}