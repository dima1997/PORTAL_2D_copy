#ifndef _MIXER_H_
#define _MIXER_H_
/*
#include "mix_chunck.h"
#include "mix_music.h"
*/
class MixChunck;
class MixMusic;

#include <string>
#include <map>
#include <vector>

class Mixer {
private:
    std::map<std::string,MixChunck> chuncks;
    std::map<std::string,MixMusic> musics;
    std::string pathMusic;

    /*
    PRE: Recibe una ruta (std::string) a un trozo de sonido.
    POST: Devuelve true si agrego el trozo de sonido al mixer,
    false en contrario dado que ya existia un trozo con dicho 
    path agregado. 
    */
    bool add_chunck(std::string pathChunck);

    /*
    Inicializa el audio del mixer.
    Levanta OSException en caso de error.
    */
    void init_audio();

public:
    /*
    PRE: Recibe el path al unico soundtrack de fondo 
    que utilizar el mixer.
    POST: Inicializa un mixer encargado 
    de manejar todos los sonidos.
    */
    Mixer(std::string pathMusic, const std::vector<std::string> &pathsChunks);

    /*
    Destruye el 
    mixer.
    */
    ~Mixer();

    /*Construccion por movimiento.*/
    Mixer(Mixer && other);

    /*Asignacion por movimiento.*/
    Mixer & operator=(Mixer && other);

    Mixer(const Mixer & other) = delete;
    Mixer & operator=(const Mixer & other) = delete;

    /*
    PRE: Recibe la ruta (std::string) de chunck agregado.
    POST: Devuelve true si logro reproducir el chunck, 
    false en caso de que el chunck no haya sido agregado.
    */
    bool play_chunck(std::string pathChunck);

    /*
    Reproduce/continua la musica de 
    fondo del mixer.
    */
    void play_music();

    /*
    Pausa la musica de fondo 
    del mixer.
    */
    void pause_music();
    
    /*
    Detiene la musca de fondo del mixer.
    (La proxima reproduccion empezara al inicio)
    */
    void stop_music();

    /*
    PRE: Recibe un volumen (int) de 0 a 128.
    POST: ajusta el volumen de la musica.
    */
    void volume_music(int volume);

    /*
    Devuelve true si la musica se esta reproduciendo, 
    y no esta pausada; false en caso contrario.
    */
    bool is_playing_music();

    /*
    Reproduce la musica si no esta sonando;
    caso contrario pause la reproduccion.
    */
    void music();
};

#endif // _MIXER_H_