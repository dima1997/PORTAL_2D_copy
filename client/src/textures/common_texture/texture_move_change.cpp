#include "../../../includes/textures/common_texture/texture_move_change.h"

#include "../../../includes/textures/common_texture/texture_change.h"
#include "../../../includes/window/window.h"

#include <protocol/event/object_moves_event.h>

/*
PRE: Recibe el id de una textura, y las nuevas 
coordenadas x,y de la misma, en el mapa de juego.
POST: Inicializa un cambio en la ubicacion de la
textura, bajo las condiciones indicadas.
*/
TextureMoveChange::TextureMoveChange(uint32_t idTexture, float newX, float newY)
: TextureChange(idTexture), newX(newX), newY(newY) {}

TextureMoveChange::TextureMoveChange(const ObjectMovesEvent &objectMovesEvent)
:   TextureChange(objectMovesEvent.getId()),
    newX(objectMovesEvent.getX()),
    newY(objectMovesEvent.getY()) {}

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
