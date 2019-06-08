#include "mix_chunck.h"

#include <SDL2/SDL_mixer.h>

#include <string>
#include <exception>
#include <sstream>

/*
PRE: Recibe una ruta a un trozo de sonido 
de terminacion : .wav .
POST: Inicializa un trozo de sonido.
*/
MixChunck::MixChunck(std::string pathSound){
    this->mixChunck = Mix_LoadWAV(pathSound.c_str());
    if (this->mixChunck == NULL){
        const std::string msg = "Error al cargar " + pathSound + "\n";  
        throw std::runtime_error(msg);
    }
}

/*Destruye el trozo de sonido.*/
MixChunck::~MixChunck(){
    Mix_FreeChunk(this->mixChunck);
}

/*Reproduce el trozo de sonido una sola vez.*/
void MixChunck::play(){
    Mix_PlayChannel(-1, this->mixChunck, 0);
}
