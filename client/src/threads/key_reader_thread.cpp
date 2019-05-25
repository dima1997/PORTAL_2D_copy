#include "../../includes/threads/key_reader_thread.h"

#include "../../../common/thread.h"
#include "../../../common/blocking_queue.h"
#include "../../../common/protocolo_code.h"

#include <SDL2/SDL.h>
#include <ctime>

#define TIME_WAIT_MILI_SECONDS 75

/*
PRE: Recibe un evento de sdl (SDL_Event &).
POST: Procesa el evento recibido. 
*/
void KeyReaderThread::process_event(SDL_Event & event){
    switch(event.type) {
        case SDL_KEYDOWN: {
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
            switch (keyEvent.keysym.sym) {
                case SDLK_LEFT:
                    this->gameActions.push(move_left);
                    break;
                case SDLK_RIGHT:
                    this->gameActions.push(move_right);
                    break;
            } // Fin KEY_DOWN
            break;
        }
        case SDL_QUIT:
            this->stop();
            this->game.stop();
            break;
    }
} 

/*
Envia al juego la accion a realizar.
*/
void KeyReaderThread::send(GameObjectAction action){
    this->gameActions.push(action);
}

/*Inicializa un lector de eventos.*/
KeyReaderThread::KeyReaderThread(uint32_t idObject, 
BlockingQueue<GameObjectAcion> & gameActions, Game & game)
:  isDead(true), idObject(idObject), gameActions(gameActions), game(game) {} 

/*Destruye el lector de eventos.*/
KeyReaderThread::~KeyReaderThread(){}

/*Ejecuta el lector de eventos.*/
void KeyReaderThread::run(){
    this->isDead = false;
    SDL_Event event;
    unsigned t0, t1, t2;
    double timeWaitMiliSeconds = TIME_WAIT_MILI_SECONDS;
    while (! this->is_dead()){
        t0 = clock();
        if (SDL_PollEvent(& event)){
            this->process_event(event);
        }
        t1 = clock();
        double timeSpendMiliSencods = (double(t1-t0)/CLOCKS_PER_SEC) * 1000;
        SDL_Delay(timeWaitMiliSeconds - timeSpendMiliSencods);
    }
    this->stop();
}

/*Detiene la ejecucion del hilo.*/
void KeyReaderThread::stop(){
    this->isDead = true;
}

/*
Devuelve true si el hilo esta muerto; 
false en caso contrario.
*/
bool KeyReaderThread::is_dead(){
    return this->isDead;
}
