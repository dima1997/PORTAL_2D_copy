#ifndef PLAYER_DIES_CHANGE_H
#define PLAYER_DIES_CHANGE_H

#include "texture_change.h"
#include "../../window/window.h"

#include <cstdint>

class PlayerDiesChange : public TextureChange { 
public:
    /*
    PRE: Recibe:
        el id de una textura seguidora;
        el id de una textura a seguir;
    POST: Inicializa un cambio donde muere un jugador.
    */
    PlayerDiesChange(
        uint32_t idPlayer
    );

    /*
    Destruye el cambio.
    */
    virtual ~PlayerDiesChange();

    /*
    PRE: Recibe un ventana (Window &) donde 
    realizar el cambio.
    POST: Realiza el cambio que representa 
    en la ventana recibida.
    */
    virtual void change(Window & window);   
    
    /*Actualiza el resultado del juego.*/
    virtual void change(PlayResult & playResult); 
};

#endif // PLAYER_DIES_CHANGE_H
