#ifndef SWS_CONTEXT_WRAPPER_H
#define SWS_CONTEXT_WRAPPER_H

extern "C" {
#include <libswscale/swscale.h>
}

class SwsContextWrapper {
private:
    int bufferWidth;
    int bufferHeight;
    SwsContext* swsContext;
public:
    /*
    PRE: Recibe el ancho y alto (ambos int) del buffer 
    a escalar.
    POST: Inicializa un contexto de sws, que escala de
    RGB24 a YUV420p.
    */
    SwsContextWrapper(int bufferWidth, int bufferHeight);

    /*Destrueye el wrapper del contextor de sws.*/
    ~SwsContextWrapper();

    /*
    PRE: Recibe 
        el buffer con la data a escalar 
        en bytes (u_int8_t *);
        la altura (int) del frame donde 
        se guardara el buffer escalado;
        la data (uint8_t *) del frame 
        donde se guardara el buffer 
        escalado;
        la dimension (int) de linea del 
        frame donde se guardara el buffer 
        escalado;
    POST: Escala el buffer recibido y lo 
    guarda el buffer del frame tambien 
    recibido.
    */
    void scale(
        const u_int8_t* bufferData, 
        int frameHeight, 
        uint8_t * const * frameData, 
        const int * frameLinesize
    );
};

#endif // SWS_CONTEXT_WRAPPER_H
