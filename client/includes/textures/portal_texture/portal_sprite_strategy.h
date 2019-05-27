#ifndef PORTAL_SPRITE_STRATEGY_H
#define PORTAL_SPRITE_STRATEGY_H

#include "../common_texture/sprite_strategy.h"

enum PortalSpriteName {
    PORTAL_OPEN,
    PORTAL_CLOSE
};

class PortalSpriteStrategy : public SpriteStrategy {
private: 
    PortalSpriteName spriteName;
public:
    /*
    Iniciliza un portal sprite strategy, cuyos sprites 
    se encuentran en la imagen PORTAL_SPRITES de 
    images_paths.h .
    */
    PortalSpriteStrategy();

    /*Destruye uel sprite strategy del portal.*/
    virtual ~PortalSpriteStrategy();

    /*
    Alterna el sprite del portal entre visible 
    y no visible.
    */
    virtual switch_sprite();
};

#endif // PORTAL_SPRITE_STRATEGY_H
