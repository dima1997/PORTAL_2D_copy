#include "../../includes/mixer/mix_music.h"

#include "../../includes/window/os_exception.h"

#include <SDL2/SDL_mixer.h>

#include <string>
#include <exception>
#include <sstream>

/*
PRE: Recibe una ruta a un soundtrack de 
terminacion: .wav .
POST: inicializa una musica del soundtrack.
*/
MixMusic::MixMusic(std::string pathMusic){
    this->mixMusic = Mix_LoadMUS(pathMusic.c_str());
    if (this->mixMusic == NULL){
        const std::string msg = "Error al cargar " + pathMusic + "\n"; 
        throw OSException(msg.c_str(),Mix_GetError());
    }
}

/*Destruye la musica del soundtrack.*/
MixMusic::~MixMusic(){
    if (this->mixMusic != NULL){
        Mix_FreeMusic(this->mixMusic);
        this->mixMusic = NULL;
    }
}

/*Construccion por movimiento.*/
MixMusic::MixMusic(MixMusic && other){
    this->mixMusic = other.mixMusic;
    other.mixMusic = NULL;
}

/*Asignacion por movimiento*/
MixMusic & MixMusic::operator=(MixMusic && other){
    if (this == & other){
        return *this;
    }
    this->mixMusic = other.mixMusic;
    other.mixMusic = NULL;
    return *this;
}

/*Inicia/continua la reproduccion del soundtrack.*/
void MixMusic::play(){
    if(Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(this->mixMusic, -1);
    } else if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    }
}

/*Pausa la reproduccion del soundtrack.*/
void MixMusic::pause(){
    if(Mix_PausedMusic() == 0){
        Mix_PauseMusic();
    }
}

/*
Detiene la reproduccion de musica, 
tras lo cual si se vuelve a reproducir, 
empezar desde el inicio del soundtrack
*/
void MixMusic::stop(){
    Mix_HaltMusic();
}

/*
PRE: Recibe un volumen de musica (int) 
de 0 a 128.
POST: ajusta el volumen de la musica, 
al indicado. 
*/
void MixMusic::volume(int volume){
    Mix_VolumeMusic(volume);
}

/*
Devuelve true, si el soundtrack se esta 
reproduciendo y no esta pausado; false 
en caso contrario.
*/
bool MixMusic::is_playing(){
    return ((Mix_PlayingMusic() == 1) && (Mix_PausedMusic() == 0));
}