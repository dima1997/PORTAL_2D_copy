#include "../../includes/threads/key_reader.h"

#include "../../includes/window/window.h"

#include <blocking_queue.h>
#include <protocol/protocol_code.h>
#include <protocol/game_action/game_action.h>
#include <protocol/game_action/coords_action.h>

#include <SDL2/SDL.h>
#include <memory>

#include <iostream>

/*
PRE: Recibe: 
    una referencia a la ventana (Window &) donde se realizan las 
    animaciones el objeto al que el lector hace referencia en 
    cada evento leido; 
    una cola bloqueante de punteros unicos a acciones del juego 
    (BlockingQueue<std::unique_ptr<GameAction>> &); 
    una cola bloqueante por donde indicarle al juego que se quiere 
    salir del mismo (BlockingQueue<GameActionName>> &);
POST: Inicializa un lector de eventos de entrada.
*/
KeyReader::KeyReader(
    Window & window,
    Mixer & mixer, 
    BlockingQueue<std::unique_ptr<GameAction>> & toGameQueue
)
:   window(window), 
    mixer(mixer),
    toGameQueue(toGameQueue), 
    keysSendOnce({
        std::make_pair<KeyUsed,bool>(SPACE, false),
        std::make_pair<KeyUsed,bool>(LSHIFT, false),
        std::make_pair<KeyUsed,bool>(V, false),
    }),
    deadKeys(false) {}

/*Destruye el lector de eventos de entrada.*/
KeyReader::~KeyReader() = default;

/*
Procesa eventos de la cola de eventos de entrada, 
hasta que esta este vacia.
Devuelve quit_game, cuando el lector recibir una peticion
para salir de juego; en caso contrario devuelve null_action
si debe seguir leyendo (GameActionName). 
*/
GameActionName KeyReader::process_some_events(){
    SDL_Event event;
    while (SDL_PollEvent(& event)){
        if (this->process_event(event) == quit_game){
            return quit_game;
        }
    }
    return null_action;
}

/*
PRE: Recibe un evento de sdl (SDL_Event &).
POST: Procesa el evento recibido.
Devuelve quit_game, cuando el lector recibir una peticion
para salir de juego; en caso contrario devuelve null_action
si debe seguir leyendo (GameActionName). 
*/
GameActionName KeyReader::process_event(SDL_Event & event){
    switch(event.type) {
        case SDL_QUIT:
            {
                GameActionName quitName = quit_game;
                std::unique_ptr<GameAction> ptrAction(
                    new GameAction(quitName)
                );
                this->toGameQueue.push(ptrAction);
                return quitName; // Podemos cambiarlo a un THREAD_STATUS
            }
            break;
        case SDL_KEYDOWN: 
            {
                auto& keyEvent = (SDL_KeyboardEvent &) event;
                this->process_event_down(keyEvent);
            }
            break;
        case SDL_KEYUP:
            {
                auto& keyEvent = (SDL_KeyboardEvent &) event;
                this->process_event_up(keyEvent);
            }
        case SDL_MOUSEBUTTONDOWN:
            {
                auto& mouseEvent = (SDL_MouseButtonEvent &) event;
                this->process_event(mouseEvent);
            }
            break;
    }
    return null_action;
} 

/*
PRE: Recibe un evento de teclado de sdl (SDL_KeyboardEvent &),
de una tecla liberada.
POST: Procesa el evento.
*/
void KeyReader::process_event_up(SDL_KeyboardEvent & keyEvent){
    switch (keyEvent.keysym.sym) {
        case SDLK_a:
        case SDLK_LEFT:
            this->process_key_up(A, stop_move);
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            this->process_key_up(D, stop_move);
            break;
        case SDLK_w:
        case SDLK_UP:
            this->process_key_up(W, null_action);
            break;
        case SDLK_SPACE:
        case SDLK_RCTRL:
            this->process_key_up(SPACE, stop_grab);
            break;
        case SDLK_LSHIFT:
        case SDLK_MINUS:
            this->process_key_up(LSHIFT, stop_throw);
            break;
        case SDLK_v:
            this->process_key_up(V, null_action);
            break;
        default:
            return;
    }
}

/*
PRE: Recibe el indicativo de la tecla liberada (KeyPressed), y el nombre
de la accion del juego a procesar segun corresponda (GameActionEvent).
POST: Comunica la accion del juego, solo si la tecla fue liberada antes de ser 
presionada.
*/
void KeyReader::process_key_up(KeyUsed actualKey, GameActionName actionName){
    if (this->keysSendOnce.count(actualKey) != 0){
        this->keysSendOnce[actualKey] = false;
    }
    if (this->deadKeys){
        return;
    }
    if (actionName == null_action){
        return;
    }
    std::unique_ptr<GameAction> ptrGameAction(new GameAction(actionName));
    this->toGameQueue.push(ptrGameAction);
}

/*
PRE: Recibe un evento de teclado de sdl (SDL_KeyboardEvent &),
de una tecla presionada.
POST: Procesa el evento.
*/
void KeyReader::process_event_down(SDL_KeyboardEvent & keyEvent){
    switch (keyEvent.keysym.sym) {
        case SDLK_a:
        case SDLK_LEFT:
            this->process_key_down(A, move_left);
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            this->process_key_down(D, move_right);
            break;
        case SDLK_w:
        case SDLK_UP:
            this->process_key_down(W, jump);
            break;
        case SDLK_SPACE:
        case SDLK_RCTRL:
            this->process_key_down(SPACE, grab_it);
            break;
        case SDLK_LSHIFT:
        case SDLK_MINUS:
            this->process_key_down(LSHIFT, throw_it);
            break;
        case SDLK_m:
            {
                if (this->mixer.is_playing_music()){
                    this->mixer.pause_music();
                } else {
                    this->mixer.play_music();
                }
            }
            break;
        case SDLK_v:
            {
                this->process_key_down(V, null_action);
            }
            break;
        default:
            return;
    }
}

/*
PRE: Recibe el indicativo de la tecla presionada (KeyPressed), y el nombre
de la accion del juego a procesar segun corresponda (GameActionEvent).
POST: Comunica la accion del juego, solo si la tecla fue liberada antes de ser 
presionada.
*/
void KeyReader::process_key_down(KeyUsed actualKey, GameActionName actionName){
    if (this->keysSendOnce.count(actualKey) != 0) {
        if (this->keysSendOnce.at(actualKey) != false){
            return;
        } else {
            this->keysSendOnce[actualKey] = true;
        }
    }
    if (actualKey == V){
        this->window.record();
        return;
    }
    if (this->deadKeys){
        return;
    }
    if (actionName == null_action) {
        return;
    }
    std::unique_ptr<GameAction> ptrGameAction(new GameAction(actionName));
    this->toGameQueue.push(ptrGameAction);
}

/*
PRE: Recibe un evento de boton de raton de sdl (SDL_MouseButtonEvent &).
POST: Procesa el evento.
*/
void KeyReader::process_event(SDL_MouseButtonEvent & mouseEvent){
    if (this->deadKeys){
        return;
    }
    int xWindow,yWindow;
    xWindow = mouseEvent.x;
    yWindow = mouseEvent.y;
    float xMap,yMap;
    std::tie(xMap,yMap) = this->window.getMapCoords(xWindow,yWindow);
    GameActionName actionName = null_action;
    switch (mouseEvent.button){
        case SDL_BUTTON_LEFT:
            actionName = open_blue_portal;
            break;
        case SDL_BUTTON_RIGHT:
            actionName = open_orange_portal;
            break;
        case SDL_BUTTON_MIDDLE:
            actionName = pin_tool_on;
            break;
        default:
            return;
    }
    std::unique_ptr<GameAction> ptrAction (
        new CoordsAction(actionName,xMap,yMap)
    );
    this->toGameQueue.push(ptrAction);   
}

/*
Hace que el lector de eventos de entrada, 
deje de procesar eventos correspondientes 
a un jugador vivo, sino que solo le permita
manejar la musica y salir del juego.
*/
void KeyReader::set_dead_keys(){
    this->deadKeys = true;
}