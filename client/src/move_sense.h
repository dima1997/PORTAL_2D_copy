#ifndef MOVE_SENSE_H
#define MOVE_SENSE_H

#include "area.h"
#include "big_texture.h" 

class MoveSense {
private:
    int lastX;
    int lastY;
    textureFlip_t flip;
public:
    /*
    Inicializa un sentido de movimiento hacia las x positivas.
    */
    MoveSense::MoveSense();
    /*Destruye el sentido de movimiento */
    ~MoveSense();

    /*
    PRE: Recibe 
        las coordenadas anteriores (in) x,y .
        las nuevas coordenadas (int) x,y .
    POST: Actualiza el sentido de moviemiento. 
    */
    void move(float xBefore, float yBefore,float xNow, float yNow);

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
