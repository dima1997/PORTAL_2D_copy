#include "../../../includes/textures/record_texture/record_paused_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

RecordPausesSprite::RecordPausesSprite(){}
RecordPausesSprite::~RecordPausesSprite() = default;

/*
Devuelve el sprite del grabado del video pausado.
IMAGE_PATH : RECORD_SPRITES
*/
DynamicSprite RecordPausesSprite::get_sprite(){
    return DynamicSprite({{0,0}},113,139);
}