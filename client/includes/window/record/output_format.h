#ifndef OUTPUT_FORMAT_H
#define OUTPUT_FORMAT_H

#include "format_context.h"
#include "codec_context_wrapper.h"

#include <string>

class OutputFormat {
private:
    FormatContext context;
    int bufferWidth;
    int bufferHeight;
    CodecContextWrapper codecContextWrapper;
public:
    /*
    PRE: Recibe: 
        el nombre de archivo de salida de 
        la grabacion;
        el ancho y alto (en pixeles) del 
        buffer de la seleccion de la 
        ventana SDL que se va a grabar.
    POST: Inicializa un formato de salida, 
    que permite grabar frames en el archivo 
    de nombre recibido.
    */
    OutputFormat(
        const std::string& fileName, 
        int bufferWidth, 
        int bufferHeight
    );

    /*
    Destruye el formate de salida, 
    primero cerrando el stream de 
    video.
    */
    ~OutputFormat();

    /*
    PRE: Recibe un buffer de bytes (const char *) del 
    frame a escribir.
    POST: Escribe el frame de la grabacion al disco.
    */
    void write_frame(const char* data); 
};

#endif // OUTPUT_FORMAT_H
