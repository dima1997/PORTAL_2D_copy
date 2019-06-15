#ifndef FORMATCONTEXT_H
#define FORMATCONTEXT_H
#include <string>

class AVFormatContext;
class FormatContext {
public:
    /*Inicializa el formate del contexto de grabacion.*/
    FormatContext();
    
    /*Destruye el contexto de grabacion*/
    ~FormatContext();

    /*Devuelve un puntero al propio (AVFormatContext *) */
    AVFormatContext* getContext() const;
private:
    AVFormatContext *pFormatCtx;
};
#endif
