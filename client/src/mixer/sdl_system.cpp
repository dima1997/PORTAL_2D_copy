#include "sdl_system.h"

#include <SDL2/SDL.h>

/*Inicializa SDL*/
SdlSystem::SdlSystem(){
    SDL_Init(0);
}

/*Finaliza todos los sistemas inicializados*/
SdlSystem::~SdlSystem(){
    if (SDL_WasInit(SDL_INIT_AUDIO) != 0){
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
    if (SDL_WasInit(SDL_INIT_VIDEO) != 0){
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
    SDL_Quit();
}

/*Inicaliza sistema de audio.*/
void SdlSystem::init_audio(){
    if (SDL_WasInit(SDL_INIT_AUDIO) == 0){
        SDL_InitSubSystem(SDL_INIT_AUDIO); // Levantar error si no funca
    }
}

/*Inicialzia sistema de video.*/
void SdlSystem::init_video(){
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0){
        SDL_InitSubSystem(SDL_INIT_VIDEO); // Levantar error si no funca
    }
}