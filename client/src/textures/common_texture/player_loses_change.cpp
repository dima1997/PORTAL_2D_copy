#include "../../../includes/textures/common_texture/player_loses_change.h"

#include "../../../includes/textures/common_texture/texture_change.h"
#include "../../../includes/window/window.h"
#include "../../../includes/threads/play_result.h"

#include <cstdint>

/*
Inicializa un cambio donde pierde 
un jugador.
*/
PlayerLosesChange::PlayerLosesChange()
:   TextureChange(0) {}

/*
Destruye el cambio.
*/
PlayerLosesChange::~PlayerLosesChange() = default;

/*Actualiza el resultado del juego.*/
void PlayerLosesChange::change(PlayResult & playResult){
    playResult.setGameStatus(LOST);
}