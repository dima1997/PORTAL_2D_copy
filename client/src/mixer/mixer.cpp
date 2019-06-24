#include "../../includes/mixer/mixer.h"

#include "../../includes/mixer/mix_chunck.h"
#include "../../includes/mixer/mix_music.h"

#include "../../includes/window/os_exception.h"

#include <SDL2/SDL_mixer.h>

#include <map>
#include <vector>
#include <string>

#define MUSIC_VOLUME 10

/*
PRE: Recibe el path al unico soundtrack de fondo 
que utilizar el mixer.
POST: Inicializa un mixer encargado 
de manejar todos los sonidos.
*/
Mixer::Mixer(std::string pathMusic, 
             const std::vector<std::string> & pathsChunks){
    // Inicializa mix audio
    this->init_audio();
    // Agrego musica de fondo
    MixMusic music(pathMusic);
    this->pathMusic = pathMusic; 
    this->musics.insert(std::make_pair<std::string,MixMusic>(
        std::move(pathMusic), std::move(music)
    ));

    // Agrego trozo de sonido
    for (int i = 0; i < (int)pathsChunks.size(); ++i){
        this->add_chunck(pathsChunks[i]);
    }

    //Inicializo volumen de musica bajo
    this->volume_music(MUSIC_VOLUME);
}

/*
Inicializa el audio del mixer.
Levanta OSException en caso de error.
*/
void Mixer::init_audio(){
    // Inicializa mix audio
    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0){
        const std::string msg = "Error: no se pudo inicializar Mixer\n";
        throw OSException(msg.c_str(),Mix_GetError());
    }
}

/*Destruye el mixer.*/
Mixer::~Mixer(){
    Mix_CloseAudio();
}

Mixer::Mixer(Mixer && other)
:   chuncks(std::move(other.chuncks)),
    musics(std::move(other.musics)),
    pathMusic(std::move(other.pathMusic)) 
{
    this->init_audio();
}

Mixer & Mixer::operator=(Mixer && other) {
    if (this == & other){
        return *this;
    }
    this->chuncks = std::move(other.chuncks);
    this->musics = std::move(other.musics);
    this->pathMusic = std::move(other.pathMusic);
    return *this; 
}

/*
PRE: Recibe una ruta (std::string) a un trozo de sonido.
POST: Devuelve true si agrego el trozo de sonido al mixer,
false en contrario dado que ya existia un trozo con dicho 
path agregado. 
*/
bool Mixer::add_chunck(std::string pathChunck){
    if (this->chuncks.count(pathChunck) != 0){
        return false;
    }
    MixChunck chunck(pathChunck);
    this->chuncks.insert(std::make_pair<std::string,MixChunck>(
        std::move(pathChunck), std::move(chunck)
    ));
    return true;
}

/*
PRE: Recibe la ruta (std::string) de chunck agregado.
POST: Devuelve true si logro reproducir el chunck, 
false en caso de que el chunck no haya sido agregado.
*/
bool Mixer::play_chunck(std::string pathChunck){
    if (this->chuncks.count(pathChunck) == 0){
        return false;
    }
    MixChunck & chunck = this->chuncks.at(pathChunck); 
    chunck.play();
    return true;
}

/*Reproduce/continua la musica de fondo del mixer.*/
void Mixer::play_music(){
    MixMusic & music = this->musics.at(this->pathMusic);
    music.play();
}

/*Pausa la musica de fondo del mixer.*/
void Mixer::pause_music(){
    MixMusic & music = this->musics.at(this->pathMusic);
    music.pause();
}
/*
Detiene la musica de fondo del mixer.
(La proxima reproduccion empezara al inicio)
*/
void Mixer::stop_music(){
    MixMusic & music = this->musics.at(this->pathMusic);
    music.stop();
}

/*
PRE: Recibe un volumen (int) de 0 a 128.
POST: ajusta el volumen de la musica.
*/
void Mixer::volume_music(int volume){
    MixMusic & music = this->musics.at(this->pathMusic);
    music.volume(volume);
}

/*
Devuelve true si la musica se esta reproduciendo, 
y no esta pausada; false en caso contrario.
*/
bool Mixer::is_playing_music(){
    MixMusic & music = this->musics.at(this->pathMusic);
    return music.is_playing();
}

/*
Reproduce la musica si no esta sonando;
caso contrario pause la reproduccion.
*/
void Mixer::music(){
    if (this->is_playing_music()){
        this->pause_music();
    } else {
        this->play_music();
    }
}