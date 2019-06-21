#ifndef START_FOLLOW_CHANGE_H
#define START_FOLLOW_CHANGE_H

#include "texture_change.h"
#include "../../window/window.h"

#include <cstdint>

class StartFollowChange : public TextureChange { 
private:
    uint32_t idFollowing;
    uint32_t idFollowed;
public:
    /*
    PRE: Recibe:
        el id de una textura seguidora;
        el id de una textura a seguir;
    POST: Inicializa un cambio de empezar a seguir
    una textura.
    */
    StartFollowChange(
        uint32_t idFollowing, 
        uint32_t idFollowed
    );

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
