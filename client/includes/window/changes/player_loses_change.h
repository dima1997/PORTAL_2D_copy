#ifndef PLAYER_LOSES_CHANGE_H
#define PLAYER_LOSES_CHANGE_H

#include "change.h"

#include <cstdint>

class Window;
class PlayResult;
class Connector;

class PlayerLosesChange : public Change { 
public:
    /*
    PRE: Recibe un connector.
    POST: Inicializa un cambio de jugador 
    que pierde.
    */
    PlayerLosesChange(Connector & connector);

    /*
    Destruye el cambio.
    */
    virtual ~PlayerLosesChange();

    /*Actualiza el resultado del juego.*/
    virtual void change(PlayResult & playResult); 
};

#endif // PLAYER_LOSES_CHANGE_H
