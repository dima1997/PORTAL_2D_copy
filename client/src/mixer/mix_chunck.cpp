#include "../../includes/mixer/mix_chunck.h"

#include "../../includes/window/os_exception.h"

#include <SDL2/SDL_mixer.h>

#include <string>

/*
PRE: Recibe una ruta a un trozo de sonido 
de terminacion : .wav .
POST: Inicializa un trozo de sonido.
*/
MixChunck::MixChunck(std::string pathSound){
    this->mixChunck = Mix_LoadWAV(pathSound.c_str());
    if (this->mixChunck == NULL){
        const std::string msg = "Error al cargar " + pathSound + "\n";  
        throw OSException(msg.c_str(),Mix_GetError());
    }
}

/*Construccion por movimiento.*/
MixChunck::MixChunck(MixChunck && other){
    this->mixChunck = other.mixChunck;
    other.mixChunck = NULL;
}

/*Asignacion por movimiento.*/
MixChunck & MixChunck::operator=(MixChunck && other){
    if (this == & other){
        return *this;
    }
    this->mixChunck = other.mixChunck;
    other.mixChunck = NULL;
    return *this;
}

/*Destruye el trozo de sonido.*/
MixChunck::~MixChunck(){
    Mix_FreeChunk(this->mixChunck);
}

/*Reproduce el trozo de sonido una sola vez.*/
void MixChunck::play(){
    Mix_PlayChannel(-1, this->mixChunck, 0);
}
