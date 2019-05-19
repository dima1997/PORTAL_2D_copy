#include "move_sense.h"

#include "area.h"
#include "big_texture.h" 

/*
Inicializa un sentido de movimiento hacia las x positivas.
*/
MoveSense::MoveSense() {
    this->flip = NO_FLIP;
}

/*Destruye el sentido de movimiento */
MoveSense::~MoveSense(){}

/*
PRE: Recibe 
    las coordenadas anteriores (in) x,y .
    las nuevas coordenadas (int) x,y .
POST: Actualiza el sentido de moviemiento. 
*/
void MoveSense::move(float xBefore, float yBefore,float xNow, float yNow){
    if (xNow < xBefore){
        this->flip = FLIP_HORIZONTAL;
    } else {
        this->flip = NO_FLIP;
    }
}

/*
PRE: Recibe:
    La gran textura (BigTexture &) con todos los sprites del jugador a usar.
    El area (Area &) del sprite especifico de la gran textura usar.
    El area (Area &) de la ventana donde se renderizara el sprite.
POST: Renderiza una textura con los datos anteriores, espejando el sprite
segun el sentido actual.
Levanta SdlException en caso de error.
*/
void MoveSense::render(BigTexture &bigTexture, 
                            const Area &src, const Area &dest){
    bigTexture.render(src, dest, this->flip);
}