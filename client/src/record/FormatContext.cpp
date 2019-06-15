#include "FormatContext.h"
#include <stdexcept>
#include <string>
extern "C" {
#include <libavformat/avformat.h>
}

/*Inicializa el formata del contexto de grabacion.*/
FormatContext::FormatContext() {
    av_register_all();
    this->pFormatCtx = avformat_alloc_context();
}

/*Destruye el contexto de grabacion*/
FormatContext::~FormatContext() {
    avformat_free_context(this->pFormatCtx);
}

/*Devuelve un puntero al propio (AVFormatContext *) */
AVFormatContext * FormatContext::getContext() const {
    return this->pFormatCtx;
}
