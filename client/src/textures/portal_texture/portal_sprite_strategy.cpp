#include "../../../includes/textures/portal_texture/portal_sprite_strategy.h"

#include "../../../includes/textures/portal_texture/portal_blue_sprite.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"
#include "../../../includes/textures/common_texture/null_sprite.h"

#include "../../../includes/mixer/sounds_path.h"

#include <memory>

/*
Iniciliza un portal sprite strategy, cuyos sprites 
se encuentran en la imagen PORTAL_SPRITES de 
images_paths.h .
*/
PortalSpriteStrategy::PortalSpriteStrategy()
:   SpriteStrategy(
        PortalBlueSprite::get_sprite()
    ), 
    spriteName(PORTAL_OPEN) {}

/*Destruye uel sprite strategy del portal.*/
PortalSpriteStrategy::~PortalSpriteStrategy() = default;

/*Alterna entre portal abierto y cerrado.*/
void PortalSpriteStrategy::switch_sprite(){
    if (this->spriteName == PORTAL_OPEN){
        this->dynamicSprite = NullSprite::get_sprite();
        this->spriteName = PORTAL_CLOSE;
    } else {
        this->dynamicSprite = PortalBlueSprite::get_sprite();
        this->spriteName = PORTAL_OPEN;
    }
}

/*
PRE: Recibe :
    las coordenadas anteriores (int) x,y de la textura que representa.
    las coordenadas nuevas (int) x,y de la textura que representa.
    una referencia a un vector de nombre de sonidos.
POST: No hace nada.
*/
void PortalSpriteStrategy::move(float xBefore, float yBefore, float xNow, float yNow, 
                          std::vector<SOUND_NAME> & sounds) {
    sounds.push_back(SOUND_PORTAL_SHOOT);
}