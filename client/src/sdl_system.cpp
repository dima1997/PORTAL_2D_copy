#include "../includes/sdl_system.h"

#include "../includes/window/os_exception.h"

#include <SDL2/SDL.h>

/*Inicializa SDL*/
SdlSystem::SdlSystem(){
    if (SDL_Init(0) < 0){
        const std::string msg = "Error al iniciar sdl.\n"; 
        throw OSException(msg.c_str(),SDL_GetError());
    }
}

/*Finaliza todos los sistemas sdl inicializados*/
SdlSystem::~SdlSystem(){
    if (SDL_WasInit(SDL_INIT_AUDIO) != 0){
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
    if (SDL_WasInit(SDL_INIT_VIDEO) != 0){
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
    SDL_Quit();
}

/*Inicializa sistema de audio de sdl.*/
void SdlSystem::init_audio(){
    if (SDL_WasInit(SDL_INIT_AUDIO) == 0){
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0){
            const std::string msg = "Error al iniciar sdl audio.\n"; 
            throw OSException(msg.c_str(),SDL_GetError());
        } 
    }
}

/*Inicializa sistema de video de sdl.*/
void SdlSystem::init_video(){
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0){
        if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0){
            const std::string msg = "Error al iniciar sdl video.\n"; 
            throw OSException(msg.c_str(),SDL_GetError());
        } 
    }
}