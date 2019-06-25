#include "../../../includes/window/changes/texture_move_change.h"

#include "../../../includes/window/window.h"

#include <protocol/event/object_moves_event.h>
#include <connector/connector.h>

/*
PRE: Recibe un connector por donde se recibira a 
continuacion un ObjectMovesEvent.
POST: Inicializa un cambio en la ubicacion de la
textura.
*/
TextureMoveChange::TextureMoveChange(Connector & connector) {
    ObjectMovesEvent event;
    connector >> event;
    this->id = event.getId();
    this->newX = event.getX();
    this->newY = event.getY();
}

/*
Destruye el cambio de ubicacion de la textura.
*/
TextureMoveChange::~TextureMoveChange() = default;

/*
PRE: Recibe un ventana (Window &) donde realizar el cambio.
POST: Realiza el cambio que representa en la ventan recibida.
*/
void TextureMoveChange::change(Window &window){
    window.move_texture(this->id, this->newX, this->newY);
}
