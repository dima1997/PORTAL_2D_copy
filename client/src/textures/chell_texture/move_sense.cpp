#include "../../../includes/textures/chell_texture/move_sense.h"

#include "../../../includes/textures/common_texture/big_texture.h" 

/*
Inicializa un sentido de movimiento 
hacia las x positivas.
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
POST: Devuelve NO_FLIP O FLIP_HORIZONTAL 
segun como debe orientarse Chell. 
*/
textureFlip_t MoveSense::update(float xBefore, float xNext){
    if (xBefore > xNext){
        this->flip =  FLIP_HORIZONTAL;
    } else if (xBefore < xNext) {
        this->flip = NO_FLIP;
    }
    return this->flip;
}