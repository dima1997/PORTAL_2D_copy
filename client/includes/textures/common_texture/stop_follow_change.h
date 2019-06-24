#ifndef STOP_FOLLOW_CHANGE_H
#define STOP_FOLLOW_CHANGE_H

#include "texture_change.h"

#include <cstdint>

class Window;
class Connector;

class StopFollowChange : public TextureChange { 
public:
    /*
    PRE: Recibe un connector por donde se recibira a 
    continuacion el id de la textura a seguir.
    POST: Inicializa el cambio.
    */
    StopFollowChange(Connector & connector);

    /*
    Destruye el cambio de seguimiento de la textura.
    */
    virtual ~StopFollowChange();

    /*
    PRE: Recibe un ventana (Window &) donde 
    realizar el cambio.
    POST: Realiza el cambio que representa 
    en la ventana recibida.
    */
    virtual void change(Window & window);
};

#endif // STOP_FOLLOW_CHANGE_H
