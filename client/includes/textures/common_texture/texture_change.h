#ifndef TEXTURE_CHANGE_H
#define TEXTURE_CHANGE_H

//#include "../../window/window.h"
//#include "../../threads/play_result.h"
//#include "../../threads/key_reader.h"

class Window;
class PlayResult;
class KeyReader;

#include <cstdint>

class TextureChange {
protected:
    uint32_t id;
public:
    /*
    PRE: Recibe el id de la textura donde se 
    realizar el cambio.
    POST: Inicializa un cambio en textura nulo.
    */
    TextureChange(uint32_t idTexture);

    /*Destruye el cambio en textura.*/
    virtual ~TextureChange();

    /*
    PRE: Recibe una ventana donde se encuentre la 
    textura con el id correspondiente a este cambio.
    POST: Realiza un cambio nulo en la ventana.
    */
    virtual void change(Window & window);

    /*
    PRE: Recibe un resultado de juego.
    POST: Realiza un cambio nulo en dicho resultado.
    */
    virtual void change(PlayResult & playResult);   

    /*
    PRE: Recibe un ventana de juego, 
    el resultado de juego, y el 
    procesardor de eventos del usuario 
    del juego.
    POST: Realiza un cambio nulo en los 
    elementos recibidos.
    */
    virtual void change(
        Window & window, 
        PlayResult & playResult, 
        KeyReader & keyReader
    );
};

#endif // TEXTURE_CHANGE_H
