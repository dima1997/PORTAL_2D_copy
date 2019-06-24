#ifndef PLAYER_REACH_CAKE_CHANGE_H
#define PLAYER_REACH_CAKE_CHANGE_H

#include "texture_change.h"

#include <cstdint>

class Window;
class PlayResult;

class PlayerReachCakeChange : public TextureChange { 
public:
    /*
    PRE: Recibe:
        el id de una textura seguidora;
        el id de una textura a seguir;
    POST: Inicializa un cambio donde gane 
    un jugador.
    */
    PlayerReachCakeChange(
        uint32_t idPlayer
    );

    /*
    Destruye el cambio.
    */
    virtual ~PlayerReachCakeChange();

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

#endif // PLAYER_REACH_CAKE_CHANGE_H
