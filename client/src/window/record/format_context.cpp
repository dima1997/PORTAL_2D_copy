#include "../../../includes/window/record/format_context.h"

extern "C" {
#include <libavformat/avformat.h>
}

/*Inicializa el formato del contexto de grabacion.*/
FormatContext::FormatContext() {
    av_register_all();
    this->pFormatCtx = avformat_alloc_context();
}

/*Destruye el formato del contexto de grabacion.*/
FormatContext::~FormatContext() {
    avformat_free_context(this->pFormatCtx);
}