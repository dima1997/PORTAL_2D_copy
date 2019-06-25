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
    virtual void switch_sprite();

    /*
    PRE: Recibe :
        las coordenadas anteriores (int) x,y de la textura que representa.
        las coordenadas nuevas (int) x,y de la textura que representa.
        una referencia a un vector de nombre de sonidos.
    POST: No hace nada.
    */
    virtual void move(float xBefore, float yBefore, float xNow, float yNow, 
              std::vector<SOUND_NAME> & sounds);
};

#endif // PORTAL_SPRITE_STRATEGY_H
