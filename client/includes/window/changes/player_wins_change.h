#ifndef PLAYER_WINS_CHANGE_H
#define PLAYER_WINS_CHANGE_H

#include "change.h"

#include <cstdint>

class Window;
class PlayResult;
class Connector;

class PlayerWinsChange : public Change { 
public:
    /*
    PRE: Recibe un connector.
    POST: Inicializa el cambio donde gana 
    un jugador.
    */
    PlayerWinsChange(Connector & connector);

    /*
    Destruye el cambio.
    */
    virtual ~PlayerWinsChange();

    /*Actualiza el resultado del juego.*/
    virtual void change(PlayResult & playResult); 
};

#endif // PLAYER_WINS_CHANGE_H
