#ifndef TEXTURE_MOVE_CHANGE_H
#define TEXTURE_MOVE_CHANGE_H

#include "texture_change.h"

#include <cstdint>

class ObjectMovesEvent;
class Window;

class TextureMoveChange : public TextureChange {
private:
    float newX;
    float newY;
public:
    /*
    PRE: Recibe el id de una textura, y las nuevas 
    coordenadas x,y de la misma, en el mapa de juego.
    POST: Inicializa un cambio en la ubicacion de la
    textura, bajo las condiciones indicadas.
    */
    TextureMoveChange(uint32_t idTexture, float newX, float newY);

    TextureMoveChange(const ObjectMovesEvent &objectMovesEvent);

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
