#include "../../includes/threads/key_reader.h"

#include "../../includes/window/window.h"

#include <blocking_queue.h>
#include <protocol/protocol_code.h>
#include <protocol/game_action/game_action.h>
#include <protocol/game_action/coords_action.h>

#include <SDL2/SDL.h>
#include <memory>

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
KeyReader::KeyReader(Window & window, 
BlockingQueue<std::unique_ptr<GameAction>> & toGameQueue, 
BlockingQueue<GameActionName> & talkRefereeQueue)
:   window(window), 
    toGameQueue(toGameQueue), 
    talkRefereeQueue(talkRefereeQueue),
    keysPressed(
        std::make_pair<KeyUsed,bool>(LEFT, false),
        std::make_pair<KeyUsed,bool>(RIGHT, false)
        std::make_pair<KeyUsed,bool>(UP, false)
    )

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
                this->talkRefereeQueue.push(quitName);
                return quitName;
            }
            break;
        case SDL_KEYDOWN: 
            {
                auto& keyEvent = (SDL_KeyboardEvent &) event;
                this->process_event_down(keyEvent);
            }
            break;
        case SDL_KEY_UP:
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
    GameActionName actionName = null_action;
    KeyPressed actualKey = NULL_KEY;
    GameActionName actionName = null_action;
    switch (keyEvent.keysym.sym) {
        case SDLK_LEFT:
            this->process_key_up(LEFT, stop_left);
            break;
        case SDLK_RIGHT:
            this->process_key_up(RIGHT, stop_right);
            break;
        case SDLK_UP:
            this->process_key_up(UP, stop_jump);
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
    this->keysPressed[actualKey] = false;
    std::unique_ptr<GameAction> ptrGameAction(new GameAction(actionName));
    this->toGameQueue.push(ptrGameAction);
}

/*
PRE: Recibe un evento de teclado de sdl (SDL_KeyboardEvent &),
de una tecla presionada.
POST: Procesa el evento.
*/
void KeyReader::process_event_down(SDL_KeyboardEvent & keyEvent){
    GameActionName actionName = null_action;
    switch (keyEvent.keysym.sym) {
        case SDLK_LEFT:
            this->process_key_down(LEFT, move_left);
            break;
        case SDLK_RIGHT:
            this->process_key_down(RIGHT, move_right);
            break;
        case SDLK_UP:
            this->process_key_down(UP, jump);
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
    if (this->keysPressed.at(actualKey) != false){
        return;
    }
    this->keysPressed.insert(actualKey, true);
    std::unique_ptr<GameAction> ptrGameAction(new GameAction(actionName));
    this->toGameQueue.push(ptrGameAction);
}

/*
PRE: Recibe un evento de boton de raton de sdl (SDL_MouseButtonEvent &).
POST: Procesa el evento.
*/
void KeyReader::process_event(SDL_MouseButtonEvent & mouseEvent){
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
        default:
            return;
    }
    std::unique_ptr<GameAction> ptrAction (
        new CoordsAction(actionName,xMap,yMap)
    );
    this->toGameQueue.push(ptrAction);   
}


