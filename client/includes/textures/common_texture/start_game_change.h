#ifndef START_GAME_CHANGE_H
#define START_GAME_CHANGE_H

#include "texture_change.h"

class TextureChange;
class Window;
class PlayResult;
class KeyReader;

#include <cstdint>

class StartGameChange : public TextureChange { 
public:
    /*
    Inicializa un cambio de inicio 
    de partida.
    */
    StartGameChange();

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
