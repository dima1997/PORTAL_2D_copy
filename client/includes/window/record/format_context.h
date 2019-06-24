#ifndef FORMAT_CONTEXT_H
#define FORMAT_CONTEXT_H

class AVFormatContext;

class FormatContext {
private:
    AVFormatContext *pFormatCtx;

public:
    /*Inicializa el formato del contexto de grabacion.*/
    FormatContext();
    
    /*Destruye el formato contexto de grabacion*/
    ~FormatContext();
};

#endif // FORMAT_CONTEXT_H
