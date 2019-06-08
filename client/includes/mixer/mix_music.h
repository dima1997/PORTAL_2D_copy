#ifndef _MIX_MUSIC_H_
#define _MIX_MUSIC_H_

#include <SDL2/SDL_mixer.h>
#include <string>

class MixMusic {
private:
    Mix_Music * mixMusic;
public:
    /*
    PRE: Recibe una ruta a un soundtrack de 
    terminacion: .wav .
    POST: inicializa una musica del soundtrack.
    */
    MixMusic(std::string pathMusic);

    /*
    Destruye la musica del 
    soundtrack.
    */
    ~MixMusic();

    /*Construccion por movimiento.*/
    MixMusic(MixMusic && other);

    /*Asignacion por movimiento*/
    MixMusic & operator=(MixMusic && other);

    MixMusic(const MixMusic & other) = delete;
    MixMusic & operator=(const MixMusic & other) = delete;    

    /*
    Inicia/continua la reproduccion 
    del soundtrack.
    */
    void play();

    /*
    Pausa la reproduccion del 
    soundtrack.
    */
    void pause();

    /*
    Detiene la reproduccion de musica, 
    tras lo cual si se vuelve a reproducir, 
    empezar desde el inicio del soundtrack
    */
    void stop();

    /*
    PRE: Recibe un volumen de musica (int) 
    de 0 a 128.
    POST: ajusta el volumen de la musica, 
    al indicado. 
    */
    void volume(int volume);

    /*
    Devuelve true, si el soundtrack se esta 
    reproduciendo y no esta pausado; false 
    en caso contrario.
    */
    bool is_playing();
};

#endif // _MIX_MUSIC_H_
