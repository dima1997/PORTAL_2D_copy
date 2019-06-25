#include "../../../includes/window/changes/player_wins_change.h"

#include "../../../includes/window/window.h"
#include "../../../includes/threads/play_result.h"

#include <connector/connector.h>

#include <cstdint>

/*
PRE: Recibe un connector.
POST: Inicializa un cambio donde gana 
un jugador.
*/
PlayerWinsChange::PlayerWinsChange(Connector & connector){
    // No necesita nada del connector.
}

/*
Destruye el cambio.
*/
PlayerWinsChange::~PlayerWinsChange() = default;

/*Actualiza el resultado del juego.*/
void PlayerWinsChange::change(PlayResult & playResult){
    playResult.setGameStatus(GAME_STATUS_WON);
}