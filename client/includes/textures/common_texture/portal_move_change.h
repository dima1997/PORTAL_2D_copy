#ifndef PORTAL_MOVE_CHANGE_H
#define PORTAL_MOVE_CHANGE_H

#include "texture_change.h"
#include "../../window/window.h"

#include <cstdint>

class PortalMoveChange : public TextureChange {
private:
    float newX;
    float newY;
    uint32_t idShooter;
    
public:
    /*
    PRE: Recibe:
        el id de una textura de portal;
        las nuevas coordenadas x,y de la misma, en el mapa de 
        juego;
        y el id de la textura quien dispara el portal.
    POST: Inicializa un cambio en la ubicacion de la
    textura del portal, bajo las condiciones indicadas.
    */
    PortalMoveChange(
        uint32_t idTexture, 
        float newX, 
        float newY, 
        uint32_t idShooter
    );

    /*
    Destruye el cambio de ubicacion de la textura.
    */
    ~PortalMoveChange();

    /*
    PRE: Recibe un ventana (Window &) donde 
    realizar el cambio.
    POST: Realiza el cambio que representa 
    en la ventana recibida.
    */
    void change(Window &window);
    
};

#endif // PORTAL_MOVE_CHANGE_H
