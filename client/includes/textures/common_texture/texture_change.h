#ifndef TEXTURE_CHANGE_H
#define TEXTURE_CHANGE_H

#include "../../../includes/window/window.h"

#include <cstdint>

class TextureChange {
protected:
    uint32_t idTexture;
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
};

#endif // TEXTURE_CHANGE_H
