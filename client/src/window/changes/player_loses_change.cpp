#include "../../../includes/window/changes/player_loses_change.h"

#include "../../../includes/window/window.h"
#include "../../../includes/threads/play_result.h"

#include <connector/connector.h>

#include <cstdint>

/*
PRE: Recibe un connector;
POST: Inicializa un cambio donde pierde 
un jugador.
*/
PlayerLosesChange::PlayerLosesChange(Connector & connector){
    // No necesita recibir nada del connetor
}

/*
Destruye el cambio.
*/
PlayerLosesChange::~PlayerLosesChange() = default;

/*Actualiza el resultado del juego.*/
void PlayerLosesChange::change(PlayResult & playResult){
    playResult.setGameStatus(GAME_STATUS_LOST);
}