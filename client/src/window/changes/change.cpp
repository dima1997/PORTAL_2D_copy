#include "../../../includes/window/changes/change.h"

#include "../../../includes/window/window.h"
#include "../../../includes/threads/play_result.h"
#include "../../../includes/threads/key_reader.h"

#include <cstdint>

/*
Inicializa un cambio en textura nulo.
*/
Change::Change() {}

/*Destruye el cambio en textura.*/
Change::~Change() = default;

/*
PRE: Recibe una ventana donde se encuentre la 
textura con el id correspondiente a este cambio.
POST: Realiza un cambio nulo en la ventana.
*/
void Change::change(Window & window) {}

/*
PRE: Recibe un resultado de juego.
POST: Realiza un cambio nulo en dicho resultado.
*/
void Change::change(PlayResult & playResult) {}

/*
PRE: Recibe un lector de eventos del usuario.
POST: Realiza un cambio nulo en dicho resultado.
*/
void Change::change(KeyReader & keyReader) {}

/*
PRE: Recibe un ventana de juego, 
el resultado de juego, y el 
procesardor de eventos del usuario 
del juego.
POST: Realiza un cambio nulo en los 
elementos recibidos.
*/
void Change::change(
    Window & window, 
    PlayResult & playResult, 
    KeyReader & keyReader
) {
    this->change(window);
    this->change(playResult);
    this->change(keyReader);
}