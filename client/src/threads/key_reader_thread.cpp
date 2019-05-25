#include "../../includes/threads/key_reader_thread.h"

#include "../../../common/thread_safe_queue.h"
#include "../../../common/thread.h"

#include <SDL2/SDL.h>

/*Inicializa un lector de eventos.*/
KeyReaderThread::KeyReaderThread(uint32_t idObject, 
TSQueueChangesAsk_t & changesAsk)
:  isDead(true), idObject(idObject), changesAsk(changesAsk) {} 
// Faltaria que reciba el socket y el id de la textura que controla

/*Destruye el lector de eventos.*/
KeyReaderThread::~KeyReaderThread(){}

/*Ejecuta el lector de eventos.*/
void KeyReaderThread::run(){
    this->isDead = false;
    SDL_Event event;
    while (! this->is_dead()){
        SDL_WaitEvent(& event);
        switch(event.type) {
            case SDL_KEYDOWN: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        this->send(MOVE_LEFT);
                        break;
                    case SDLK_RIGHT:
                        this->send(MOVE_RIGHT);
                        break;
                } // Fin KEY_DOWN
                break;
            }
            case SDL_QUIT:
                this->stop();
                //cuando este hilo este muerto sabre cuando detener al resto.
                break;
        }
    }
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

/*
Envia al juego la accion a realizar.
*/
void KeyReaderThread::send(gameObjectAction_t action){
    std::pair<uint32_t,gameObjectAction_t> change(this->idObject, action);
    this->changesAsk.push(change);
}
