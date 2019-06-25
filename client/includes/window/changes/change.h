#ifndef CHANGE_H
#define CHANGE_H

class Window;
class PlayResult;
class KeyReader;

#include <cstdint>

class Change {
public:
    /*
    Inicializa un cambio en textura nulo.
    */
    Change();

    /*Destruye el cambio en textura.*/
    virtual ~Change();

    /*
    PRE: Recibe una ventana donde se encuentre la 
    textura con el id correspondiente a este cambio.
    POST: Realiza un cambio nulo en la ventana.
    */
    virtual void change(Window & window);

    /*
    PRE: Recibe un resultado de juego.
    POST: Realiza un cambio nulo en dicho resultado.
    */
    virtual void change(PlayResult & playResult); 

    /*
    PRE: Recibe un lector de eventos del usuario.
    POST: Realiza un cambio nulo en dicho resultado.
    */
    virtual void change(KeyReader & keyReader);  

    /*
    PRE: Recibe un ventana de juego, 
    el resultado de juego, y el 
    procesardor de eventos del usuario 
    del juego.
    POST: Realiza un cambio nulo en los 
    elementos recibidos.
    */
    virtual void change(
        Window & window, 
        PlayResult & playResult, 
        KeyReader & keyReader
    );
};

#endif // CHANGE_H
