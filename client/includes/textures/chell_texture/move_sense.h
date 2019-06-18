#ifndef MOVE_SENSE_H
#define MOVE_SENSE_H

#include "../common_texture/area.h"
#include "../common_texture/big_texture.h" 

class MoveSense {
private:
    textureFlip_t flip;
public:
    /*
    Inicializa un sentido de movimiento hacia las x positivas.
    */
    MoveSense();
    
    /*Destruye el sentido de movimiento */
    ~MoveSense();

    /*
    PRE: Recibe: 
        la coordenada x (float) anterior.
        la coordenada x (float) posterior.
    POST: Actualiza el sentido de movimiento. 
    */
    void update(float xBefore, float xNext);

    /*
    PRE: Recibe:
        La gran textura (BigTexture &) con todos los sprites del jugador a usar.
        El area (Area &) del sprite especifico de la gran textura usar.
        El area (Area &) de la ventana donde se renderizara el sprite.
    POST: Renderiza una textura con los datos anteriores, espejando el sprite
    segun el sentido actual.
    Levanta SdlException en caso de error.
    */
    void render(BigTexture &bigTexture, const Area &src, const Area &dest);    
};

#endif // MOVE_SENSE_H
