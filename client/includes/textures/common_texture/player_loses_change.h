#ifndef PLAYER_LOSES_CHANGE_H
#define PLAYER_LOSES_CHANGE_H

#include "texture_change.h"
#include "../../window/window.h"

#include <cstdint>

class PlayerLosesChange : public TextureChange { 
public:
    /*
    Inicializa un cambio donde pierde 
    un jugador.
    */
    PlayerLosesChange();

    /*
    Destruye el cambio.
    */
    virtual ~PlayerLosesChange();

    /*Actualiza el resultado del juego.*/
    virtual void change(PlayResult & playResult); 
};

#endif // PLAYER_LOSES_CHANGE_H
