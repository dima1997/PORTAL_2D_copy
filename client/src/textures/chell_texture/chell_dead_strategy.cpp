#include "../../../includes/textures/chell_texture/chell_dead_strategy.h"

#include "../../../includes/textures/chell_texture/chell_dying_sprite.h"

#include "../../../includes/textures/common_texture/null_sprite.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/area.h"

/*Inicializa el estado de sprite de Chell muerta.*/
ChellDeadStrategy::ChellDeadStrategy()
:   SpriteStrategy(ChellDyingSprite::get_sprite()),
    spriteName(CHELL_SPRITE_DYING) {}

/*Destruye el estado de sprite de Chell muerta*/
ChellDeadStrategy::~ChellDeadStrategy() = default;

/*Actualiza el sprite.*/
void ChellDeadStrategy::update(){
    this->dynamicSprite.update();
    if (this->spriteName != CHELL_SPRITE_DEAD){
        if (this->dynamicSprite.is_last_sprite()) { 
            this->dynamicSprite = NullSprite::get_sprite();
            this->spriteName = CHELL_SPRITE_DEAD;
        }
    }
}