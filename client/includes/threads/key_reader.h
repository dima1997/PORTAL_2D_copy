#ifndef KEY_READER_H
#define KEY_READER_H

#include "../window/window.h"

#include <blocking_queue.h>
#include <protocol/protocol_code.h>
#include <protocol/game_action/game_action.h>
#include <protocol/game_action/coords_action.h>

#include <SDL2/SDL.h>
#include <memory>

typedef enum KeyUsed {
    NULL_KEY,
    LEFT,
    RIGHT,
    UP
} KeyUsed_t;

class KeyReader {
private:
    Window & window; 
    BlockingQueue<std::unique_ptr<GameAction>> & toGameQueue; 
    BlockingQueue<GameActionName> & talkRefereeQueue;
    std::map<KeyUsed_t,bool> keysPressed;

    /*
    PRE: Recibe un evento de teclado de sdl (SDL_KeyboardEvent &),
    de una tecla liberada.
    POST: Procesa el evento.
    */
    void process_event_up(SDL_KeyboardEvent & keyEvent);

    /*
    PRE: Recibe el indicativo de la tecla liberada (KeyPressed), 
    y el nombre de la accion del juego a procesar segun corresponda 
    (GameActionEvent).
    POST: Comunica la accion del juego, solo si la tecla fue liberada 
    antes de ser presionada.
    */
    void process_key_up(KeyUsed actualKey, GameActionName actionName);

    /*
    PRE: Recibe un evento de teclado de sdl (SDL_KeyboardEvent &),
    de una tecla presionada.
    POST: Procesa el evento.
    */
    void process_event_down(SDL_KeyboardEvent & keyEvent);

    /*
    PRE: Recibe el indicativo de la tecla presionada (KeyPressed), 
    y el nombre de la accion del juego a procesar segun corresponda 
    (GameActionEvent).
    POST: Comunica la accion del juego, solo si la tecla fue liberada 
    antes de ser presionada.
    */
    void process_key_down(KeyUsed actualKey, GameActionName actionName);
    
    /*
    PRE: Recibe un evento de boton de raton de sdl (SDL_MouseButtonEvent &).
    POST: Procesa el evento.
    */
    void process_event(SDL_MouseButtonEvent & mouseEvent);

public:
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
    KeyReader(Window & window, 
    BlockingQueue<std::unique_ptr<GameAction>> & toGameQueue, 
    BlockingQueue<GameActionName> & talkRefereeQueue);

    /*Destruye el lector de eventos de entrada.*/
    ~KeyReader();

    /*
    PRE: Recibe un evento de sdl (SDL_Event &).
    POST: Procesa el evento recibido.
    Devuelve quit_game, cuando el lector recibir una peticion
    para salir de juego; en caso contrario devuelve null_action
    si debe seguir leyendo. 
    */
    GameActionName process_event(SDL_Event & event);

    /*
    Procesa eventos de la cola de eventos de entrada, 
    hasta que esta este vacia.
    Devuelve quit_game, cuando el lector recibir una peticion
    para salir de juego; en caso contrario devuelve null_action
    si debe seguir leyendo (GameActionName). 
    */
    GameActionName process_some_events();
};

#endif // KEY_READER_H
