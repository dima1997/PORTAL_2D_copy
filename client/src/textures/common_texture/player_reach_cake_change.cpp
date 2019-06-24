#include "../../../includes/textures/common_texture/player_reach_cake_change.h"

#include "../../../includes/textures/common_texture/texture_change.h"
#include "../../../includes/window/window.h"
#include "../../../includes/threads/play_result.h"
#include "../../../includes/threads/key_reader.h"

#include <connector/connector.h>

#include <cstdint>

/*
PRE: Recibe un connector que vaya a recibir 
a continuacion:
    el id del jugador ganadors.
POST: Inicializa un cambio donde gane
un jugador.
*/
PlayerReachCakeChange::PlayerReachCakeChange(Connector & connector)
:   TextureChange(0) {
    connector >> this->id;
}

/*
Destruye el cambio.
*/
PlayerReachCakeChange::~PlayerReachCakeChange() = default;

/*
PRE: Recibe un ventana (Window &) donde 
realizar el cambio.
POST: Realiza el cambio que representa 
en la ventana recibida.
*/
void PlayerReachCakeChange::change(Window &window){
    window.switch_texture(this->id);
    window.switch_texture(this->id); // x2
}  

/*Actualiza el resultado del juego.*/
void PlayerReachCakeChange::change(PlayResult & playResult){
    playResult.setPlayerStatus(this->id, PLAYER_STATUS_CAKE);
}

/*
Actualiza: 
    la textura principal del la ventana;
    el resultado de juego;
    y el input del usuario;
*/
void PlayerReachCakeChange::change(
    Window & window, 
    PlayResult & playResult, 
    KeyReader & keyReader
) {
    this->change(window);
    this->change(playResult);
    uint32_t mainPlayerId = window.get_main_id();
    if (! playResult.is_player_alive(mainPlayerId)){
        keyReader.set_dead_keys();
        uint32_t playerIdAlive = playResult.get_player_alive();
        if (playerIdAlive != (uint32_t)(-1)){
            window.set_main_id(playerIdAlive);
        }
    }
}