#ifndef PLAYER_WINS_CHANGE_H
#define PLAYER_WINS_CHANGE_H

#include "texture_change.h"
#include "../../window/window.h"

#include <cstdint>

class PlayerWinsChange : public TextureChange { 
public:
    /*
    Inicializa un cambio donde gana 
    un jugador.
    */
    PlayerWinsChange();

    /*
    Destruye el cambio.
    */
    virtual ~PlayerWinsChange();

    /*Actualiza el resultado del juego.*/
    virtual void change(PlayResult & playResult); 
};

#endif // PLAYER_WINS_CHANGE_H
