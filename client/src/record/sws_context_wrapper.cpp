#include "sws_context_wrapper.h"

extern "C" {
#include <libswscale/swscale.h>
}

/*
PRE: Recibe el ancho y alto (ambos int) del buffer 
a escalar.
POST: Inicializa un contexto de sws, que escala de
RGB24 a YUV420p.
*/
SwsContextWrapper::SwsContextWrapper(int bufferWidth, int bufferHeight)
:   bufferWidth(bufferWidth), bufferHeight(bufferHeight){
    this->swsContext = sws_getContext(
        this->bufferWidth, 
        this->bufferHeight,
        AV_PIX_FMT_RGB24, 
        this->bufferWidth, 
        this->bufferHeight,
        AV_PIX_FMT_YUV420P,
        0, 
        0, 
        0, 
        0
    );
}

/*Destrueye el wrapper del contextor de sws.*/
SwsContextWrapper::~SwsContextWrapper(){
    sws_freeContext(this->swsContext);
}

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
void SwsContextWrapper::scale(
    const u_int8_t* bufferData, 
    int frameHeight, 
    uint8_t * const * frameData, 
    const int * frameLinesize
){  
    int width = this->bufferWidth * 3;
    sws_scale(
        this->swsContext, 
        &bufferData, 
        &width, 
        0, 
        frameHeight, 
        frameData, 
        frameLinesize
    );
}
