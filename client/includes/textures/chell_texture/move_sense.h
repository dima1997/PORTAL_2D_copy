#ifndef MOVE_SENSE_H
#define MOVE_SENSE_H

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
    POST: Devuelve NO_FLIP O FLIP_HORIZONTAL 
    segun como debe orientarse Chell.  
    */
    textureFlip_t update(float xBefore, float xNext);
};

#endif // MOVE_SENSE_H
