#ifndef START_FOLLOW_CHANGE_H
#define START_FOLLOW_CHANGE_H

#include "change.h"

#include <cstdint>

class Window;
class Connector;

class StartFollowChange : public Change { 
private:
    uint32_t idFollowing;
    uint32_t idFollowed;
public:
    /*
    PRE: Recibe un connector por donde se recibira a 
    continuacion el id de la textura seguidora, y
    luego la textura a seguir.
    POST: Inicializa el cambio.
    */
    StartFollowChange(Connector & connector);

    /*
    Destruye el cambio de seguimiento de la textura.
    */
    virtual ~StartFollowChange();

    /*
    PRE: Recibe un ventana (Window &) donde 
    realizar el cambio.
    POST: Realiza el cambio que representa 
    en la ventana recibida.
    */
    virtual void change(Window & window);
};

#endif // START_FOLLOW_CHANGE_H
