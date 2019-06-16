#include "../../../includes/window/record/output_format.h"

#include "../../../includes/window/record/format_context.h"
#include "../../../includes/window/record/codec_context_wrapper.h"

#include <cstdio>
#include <string>
#include <stdexcept>

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
OutputFormat::OutputFormat(
    const std::string& fileName, 
    int bufferWidth, 
    int bufferHeight) 
:   context(), 
    bufferWidth(bufferWidth), 
    bufferHeight(bufferHeight),
    codecContextWrapper(fileName,bufferWidth,bufferHeight) { 
}


/*
Destruye el formate de salida, 
primero cerrando el stream de 
video.
*/
OutputFormat::~OutputFormat() = default;

/*
PRE: Recibe un buffer de bytes (const char *) del 
frame a escribir.
POST: Escribe el frame de la grabacion al disco.
*/
void OutputFormat::write_frame(const char* data) {
    const u_int8_t* tmp = (const u_int8_t*) data;
    this->codecContextWrapper.encode(tmp);
}
