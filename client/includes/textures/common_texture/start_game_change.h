#ifndef START_GAME_CHANGE_H
#define START_GAME_CHANGE_H

#include "texture_change.h"

#include <cstdint>

class Window;
class PlayResult;
class KeyReader;
class Connector;

class StartGameChange : public TextureChange { 
public:
    /*
    PRE: Recibe un connector.
    POST: Inicializa el cambio de inicio 
    de juego.
    */
    StartGameChange(Connector & connector);

    /*
    Destruye el cambio.
    */
    virtual ~StartGameChange();

    /*
    Habilita deshabilita la pantalla de partida 
    cargando, y habilita todo el input del 
    usuario.
    */
    virtual void change(
        Window & window, 
        PlayResult & playResult, 
        KeyReader & keyReader
    );
};

#endif // START_GAME_CHANGE_H
