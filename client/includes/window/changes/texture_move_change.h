#ifndef TEXTURE_MOVE_CHANGE_H
#define TEXTURE_MOVE_CHANGE_H

#include "change.h"

#include <cstdint>

class Window;
class Connector;

class TextureMoveChange : public Change {
private:
    uint32_t id;
    float newX;
    float newY;
public:
    /*
    PRE: Recibe un connector por donde se recibira a 
    continuacion un ObjectMoveEvent.
    POST: Inicializa el cambio.
    */
    TextureMoveChange(Connector & connector);

    /*
    Destruye el cambio de ubicacion de la textura.
    */
    virtual ~TextureMoveChange();

    /*
    PRE: Recibe un ventana (Window &) donde realizar el cambio.
    POST: Realiza el cambio que representa en la ventan recibida.
    */
    virtual void change(Window & window);
};

#endif // TEXTURE_MOVE_CHANGE_H
