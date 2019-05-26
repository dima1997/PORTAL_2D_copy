#include "../../includes/threads/key_reader_thread.h"

#include <thread.h>
#include <blocking_queue.h>
#include <protocol/protocol_code.h>

#include <SDL2/SDL.h>
#include <ctime>
#include <memory>

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
                    this->push_action(move_left);
                    break;
                case SDLK_RIGHT:
                    this->push_action(move_right);
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
PRE: Recibe el nombre de una accion del juego (GamaActionName).
POST: Encola en la cola de acciones del juego, la accion correspondiente
al nombre de accion recibido.
*/
void KeyReaderThread::push_action(GameActionName actionName){
    std::unique_ptr<GameAction> ptrGameAction(new GameAction(actionName));
    this->gameActions.push(ptrGameAction);
}

/*
PRE: Recibe un referencia constante al area (const Area &) 
el objecto al que el lector hace referencia en cada acccion 
leida; una cola bloqueante de punteros unicos a acciones del 
juego (BlockingQueue<std::unique_ptr<GameAction>> &), y una 
referencia al juego (Game &).
POST: Inicializa un lector de eventos.
*/
KeyReaderThread::KeyReaderThread(const Area & areaMainObject, 
BlockingQueue<std::unique_ptr<GameAction>> & gameActions, Game & game)
:   isDead(true), 
    areaMainObject(areaMainObject), 
    gameActions(gameActions), 
    game(game) {} 

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
