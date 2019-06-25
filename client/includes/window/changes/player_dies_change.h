#ifndef PLAYER_DIES_CHANGE_H
#define PLAYER_DIES_CHANGE_H

#include "change.h"

#include <cstdint>

class Window;
class PlayResult;
class KeyReader;
class Connector;

class PlayerDiesChange : public Change { 
private:
    uint32_t id;

public:
    /*
    PRE: Recibe un connector por donde se vaya a recibir 
    a continuacion:
        el id de una textura seguidora;
        el id de una textura a seguir;
    POST: Inicializa un cambio donde muere un jugador.
    */
    PlayerDiesChange(Connector & connector);

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

    /*
    Actualiza: 
        la textura principal del la ventana;
        el resultado de juego;
        y el input del usuario;
    */
    virtual void change(
        Window & window, 
        PlayResult & playResult, 
        KeyReader & keyReader
    );
};

#endif // PLAYER_DIES_CHANGE_H
