#ifndef RECORDING_SPRITE_H
#define RECORDING_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class RecordingSprite{
public:
    RecordingSprite();
    ~RecordingSprite();
    
    /*
    Devuelve el sprite del video siendo grabado.
    IMAGE_PATH : RECORD_SPRITES
    */
    static DynamicSprite get_sprite();    
};

#endif // RECORDING_SPRITE_H
