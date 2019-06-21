#include "../../../includes/textures/common_texture/player_dies_change.h"

#include "../../../includes/textures/common_texture/texture_change.h"
#include "../../../includes/window/window.h"

#include <cstdint>

/*
PRE: Recibe:
    el id de una textura seguidora;
    el id de una textura a seguir;
POST: Inicializa un cambio donde muere 
un jugador.
*/
PlayerDiesChange::PlayerDiesChange(
    uint32_t idPlayer 
)
:   TextureChange(idPlayer) {}

/*
Destruye el cambio.
*/
PlayerDiesChange::~PlayerDiesChange() = default;

/*
PRE: Recibe un ventana (Window &) donde 
realizar el cambio.
POST: Realiza el cambio que representa 
en la ventana recibida.
*/
void PlayerDiesChange::change(Window &window){
    window.switch_texture(this->id);
}  

/*Actualiza el resultado del juego.*/
void PlayerDiesChange::change(PlayResult & playResult){
    playResult.setPlayerStatus(this->id, DEAD);
}