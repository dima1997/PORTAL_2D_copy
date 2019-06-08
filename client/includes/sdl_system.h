#ifndef _SDL_SYSTEM_H_
#define _SDL_SYSTEM_H_

class SdlSystem {
public:
    /*Inicializa SDL*/
    SdlSystem();

    /*Finaliza todos los sistemas inicializados.*/
    ~SdlSystem();

    /*Inicaliza sistema de audio.*/
    void init_audio();

    /*Inicialzia sistema de video.*/
    void init_video();
};

#endif // _SDL_SYSTEM_H_
