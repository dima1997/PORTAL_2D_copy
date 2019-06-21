#ifndef STOP_FOLLOW_CHANGE_H
#define STOP_FOLLOW_CHANGE_H

#include "texture_change.h"
#include "../../window/window.h"

#include <cstdint>

class StopFollowChange : public TextureChange { 
public:
    /*
    PRE: Recibe:
        el id de una textura seguidora;
        el id de una textura a seguir;
    POST: Inicializa un cambio de dejar de seguir
    una textura.
    */
    StopFollowChange(
        uint32_t idFollowing
    );

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
