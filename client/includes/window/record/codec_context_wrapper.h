#ifndef CODEC_CONTEXT_WRAPPER_H
#define CODEC_CONTEXT_WRAPPER_H

#include "sws_context_wrapper.h"

extern "C" {
#include <libswscale/swscale.h>
}

#include <cstdio>
#include <string>
#include <stdexcept>

class AVCodecContext;
class AVFrame;
class AVPacket;
class AVOutputFormat;
class AVCodec;

class CodecContextWrapper {
private:
    int bufferWidth;
    int bufferHeight;
    int currentPts;
    AVCodecContext* codecContext;
    AVFrame* frame;
    AVPacket* pkt;
    FILE* outputFile;
    SwsContextWrapper swsContextWrapper;

    /*
    PRE: Recibe el nombre (const std::string &) 
    del archivo grabacion de salida.
    POST: Devuelve el formato de salida a 
    utilizar (AVOutputFormat *).
    */
    AVOutputFormat * get_av_output_format(
        const std::string & fileName
    );

    /*
    PRE: Recibe el formato de salida (AVOutputFormat *) 
    del archivo de grabacion.
    POST: Devuelve una instancia de codec (AVCodec *), 
    para dicho formato.
    */
    AVCodec * get_av_codec(
        AVOutputFormat * avOutputFormat
    );

    /*
    PRE: Recibe el codec especifico para el 
    archivo de grabacion de salida.
    POST: Inicializa el contexto de codec.
    */
    void init_codec_context(AVCodec* codec);

    /*
    PRE: El contexto de codec debe estar 
    inicializado.
    POST: Inicializa el frame.
    */
    void init_frame();

    /*Inicializa el packet.*/
    void init_packet();
    
    /*Cierra el stream del video.*/
    void close();

    /*
    PRE: Recibe el frame (AVFrame* frame) 
    a codificar, NULL para finalizar el 
    stream.
    POST: Codifica y escribe al archivo de 
    salida de grabacion el frame actual.
    */
    void _encode(AVFrame* frame);
    
public:
    /*
    PRE: Recibe: 
        el nombre del archivo de salido de 
        grabacion;
        ancho y alto (int) del buffer 
        que se va a decodificar;
    POST: Inicializa un wrapper del contexto 
    de codec.
    */
    CodecContextWrapper(
        const std::string& fileName,
        int bufferWidth, 
        int bufferHeight
    );

    /*Destruye el wrapper del contexto de codec.*/
    ~CodecContextWrapper();

    /*
    PRE: Recibe un buffer de bytes (const u_int8_t*) 
    del frame a escribir.
    POST: Escribe el frame de la grabacion al disco 
    (al archivo de salida de grabacion).
    */
    void encode(const u_int8_t* bufferData);
};

#endif // CODEC_CONTEXT_WRAPPER_H
