#ifndef OUTPUTFORMAT_H
#define OUTPUTFORMAT_H
#include <string>

#include "FormatContext.h"
#include "sws_context_wrapper.h"
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}

/**
 * Clase que encapsula lógica la salida de video
 * Se recomienda modularizar aun más esta clase, reforzando RAII
 */
class OutputFormat {
private:
    FormatContext context;
    int bufferWidth;
    int bufferHeight;
    int currentPts;
    AVCodecContext* codecContext;
    SwsContext* swsContext;
    AVFrame* frame;
    AVPacket* pkt;
    FILE* outputFile;

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
    PRE: Recibe el formato de salida del 
    archivo de grabacion.
    POST: Devuelve una instancia de codec 
    (AVCodec *), para dicho formato.
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
    
    /*Inicializa el contexto de SWS.*/
    void init_sws_context();
    
    /*Inicializa el frame.*/
    void init_frame();

    /*Inicializa el packet.*/
    void init_packet();
    
public:
    // Ctor
    OutputFormat(
        const std::string& filename, 
        int bufferWidth, 
        int bufferHeight
    );  
    // Dtor
    ~OutputFormat();
    // Escribe un frame a disco. 
    void writeFrame(const char* data); 
    // Cierra el stream de video
    void close();
};
#endif
