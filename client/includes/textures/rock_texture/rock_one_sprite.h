#ifndef ROCK_ONE_SPRITE_H
#define ROCK_ONE_SPRITE_H

#include "../common_texture/dynamic_sprite.h"

class RockOneSprite : public DynamicSprite {
public:
    /*Inicializa un sprite de roca de tipo 1.*/
    RockOneSprite();

    /*Destruye el sprite de roca de tipo 1.*/
    virtual ~RockOneSprite();
};

#endif // ROCK_ONE_SPRITE_H
