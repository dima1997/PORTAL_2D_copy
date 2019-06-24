#include "../../../includes/textures/common_texture/player_wins_change.h"

#include "../../../includes/textures/common_texture/texture_change.h"
#include "../../../includes/window/window.h"
#include "../../../includes/threads/play_result.h"

#include <cstdint>

/*
Inicializa un cambio donde gana 
un jugador.
*/
PlayerWinsChange::PlayerWinsChange()
:   TextureChange(0) {}

/*
Destruye el cambio.
*/
PlayerWinsChange::~PlayerWinsChange() = default;

/*Actualiza el resultado del juego.*/
void PlayerWinsChange::change(PlayResult & playResult){
    playResult.setGameStatus(WON);
}