#ifndef KEY_READER_H
#define KEY_READER_H

class Window;
class Mixer;

#include <blocking_queue.h>
#include <protocol/protocol_code.h>
#include <protocol/game_action/game_action.h>
#include <protocol/game_action/coords_action.h>

#include <SDL2/SDL.h>

#include <map>
#include <memory>

enum KeyUsed {
    NULL_KEY,
    A,
    D,
    W,
    SPACE,
    E,
    Q,
    R,
    K,
    V,
    M,
    EXIT
};

class KeyReader {
private:
    Window & window; 
    Mixer & mixer;
    BlockingQueue<std::unique_ptr<GameAction>> & toGameQueue; 
    std::map<KeyUsed,bool> keysSendOnce;
    bool deadKeys;

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
    KeyReader(
        Window & window,
        Mixer & mixer, 
        BlockingQueue<std::unique_ptr<GameAction>> & toGameQueue
    );

    /*Destruye el lector de eventos de entrada.*/
    ~KeyReader();

    /*
    PRE: Recibe un evento de sdl (SDL_Event &).
    POST: Procesa el evento recibido.
    Devuelve THREAD_STOP, cuando el lector recibir una peticion
    para salir de juego; en caso contrario devuelve THREAD_GO
    si debe seguir leyendo (ThreadStatus). 
    */
    ThreadStatus process_event(SDL_Event & event);

    /*
    Procesa eventos de la cola de eventos de entrada, 
    hasta que esta este vacia.
    Devuelve THREAD_STOP, cuando el lector recibir una peticion
    para salir de juego; en caso contrario devuelve THREAD_GO
    si debe seguir leyendo (ThreadStatus). 
    */
    ThreadStatus process_some_events();

    /*
    Hace que el lector de eventos de entrada, 
    deje de procesar eventos correspondientes 
    a un jugador vivo, sino que solo le permita
    manejar la musica y salir del juego.
    */
    void set_dead_keys();

    /*
    Hace que el lector de eventos proceso 
    todos los eventos del usuario.
    */
    void set_alive_keys();
};

#endif // KEY_READER_H
