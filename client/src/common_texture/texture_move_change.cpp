#include "texture_move_change.h"

/*
PRE: Recibe el id de una textura, y las nuevas 
coordenadas x,y de la misma, en el mapa de juego.
POST: Inicializa un cambio en la ubicacion de la
textura, bajo las condiciones indicadas.
*/
TextureMoveChange::TextureMoveChange(uint32_t idTexture, float newX, float newY)
: idTexture(idTexture), newX(newX), newY(newY) {}

/*
Destruye el cambio de ubicacion de la textura.
*/
TextureMoveChange::~TextureMoveChange(){}

/*
PRE: Recibe un ventana (Window &) donde realizar el cambio.
POST: Realiza el cambio que representa en la ventan recibida.
*/
void TextureMoveChange::change(Window &window){
    window.move_texture(this->idTexture, this->newX, this->newY);
}

