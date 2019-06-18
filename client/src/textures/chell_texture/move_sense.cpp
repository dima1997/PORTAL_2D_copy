#include "../../../includes/textures/chell_texture/move_sense.h"

#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h" 

/*
Inicializa un sentido de movimiento hacia las x positivas.
*/
MoveSense::MoveSense() {
    this->flip = NO_FLIP;
}

/*Destruye el sentido de movimiento */
MoveSense::~MoveSense() = default;

/*
PRE: Recibe 
    la coordenada x (float) anterior.
    la coordenada x (float) posterior.
POST: Actualiza el sentido de movimiento. 
*/
void MoveSense::update(float xBefore, float xNext){
    if (xBefore < xNext){
        this->flip = NO_FLIP;
    } else {
        this->flip = FLIP_HORIZONTAL;
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
