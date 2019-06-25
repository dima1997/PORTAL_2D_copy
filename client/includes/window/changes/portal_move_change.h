#ifndef PORTAL_MOVE_CHANGE_H
#define PORTAL_MOVE_CHANGE_H

#include "change.h"

#include <cstdint>

class Window;
class Connector;

class PortalMoveChange : public Change {
private:
    uint32_t idPortal;
    float newX;
    float newY;
    uint32_t idShooter;
    float normalX;
    float normalY;
    
public:
    /*
    PRE: Recibe un connector por donde se vaya a recibir a 
    continuacion un PortalMoveEvent.
    POST: Inicializa el cambio.
    */
    PortalMoveChange(Connector & connector);

    /*
    Destruye el cambio de ubicacion de la textura.
    */
    virtual ~PortalMoveChange();

    /*
    PRE: Recibe un ventana (Window &) donde 
    realizar el cambio.
    POST: Realiza el cambio que representa 
    en la ventana recibida.
    */
    virtual void change(Window &window); 
};

#endif // PORTAL_MOVE_CHANGE_H
