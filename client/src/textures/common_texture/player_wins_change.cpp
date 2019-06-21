#include "../../../includes/textures/common_texture/player_wins_change.h"

#include "../../../includes/textures/common_texture/texture_change.h"
#include "../../../includes/window/window.h"

#include <cstdint>

/*
PRE: Recibe:
    el id del jugador que gana
POST: Inicializa un cambio donde gana 
un jugador.
*/
PlayerWinsChange::PlayerWinsChange(
    uint32_t idPlayer 
)
:   TextureChange(idPlayer) {}

/*
Destruye el cambio.
*/
PlayerWinsChange::~PlayerWinsChange() = default;

/*Actualiza el resultado del juego.*/
void PlayerWinsChange::change(PlayResult & playResult){
    playResult.setGameStatus(WON);
}