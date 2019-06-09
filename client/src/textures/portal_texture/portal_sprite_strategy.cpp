#include "../../../includes/textures/portal_texture/portal_sprite_strategy.h"

#include "../../../includes/textures/portal_texture/portal_blue_sprite.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"
#include "../../../includes/textures/common_texture/dynamic_sprite.h"
#include "../../../includes/textures/common_texture/null_sprite.h"
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
/*
:   SpriteStrategy(
        std::move(
            std::unique_ptr<DynamicSprite>(new PortalBlueSprite())
        )    
    ), spriteName(PORTAL_OPEN) {}
*/

/*Destruye uel sprite strategy del portal.*/
PortalSpriteStrategy::~PortalSpriteStrategy() = default;

void PortalSpriteStrategy::switch_sprite(){
    if (this->spriteName == PORTAL_OPEN){
        //this->ptrDynamicSprite.reset(new NullSprite());
        this->dynamicSprite = NullSprite::get_sprite();
        this->spriteName = PORTAL_CLOSE;
    } else {
        //this->ptrDynamicSprite.reset(new PortalBlueSprite());
        this->dynamicSprite = PortalBlueSprite::get_sprite();
        this->spriteName = PORTAL_OPEN;
    }
}