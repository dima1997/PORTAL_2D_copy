#include "../../../includes/window/changes/player_dies_change.h"

#include "../../../includes/window/window.h"
#include "../../../includes/threads/play_result.h"
#include "../../../includes/threads/key_reader.h"

#include <connector/connector.h>

#include <cstdint>

/*
PRE: Recibe un connector por donde se recibira a 
continuacion el ide de un jugador muerto.
POST: Inicializa un cambio donde muere 
un jugador.
*/
PlayerDiesChange::PlayerDiesChange(Connector & connector){
    connector >> this->id;
}

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
    playResult.setPlayerStatus(this->id, PLAYER_STATUS_DEAD);
}

/*
Actualiza: 
    la textura principal del la ventana;
    el resultado de juego;
    y el input del usuario;
*/
void PlayerDiesChange::change(
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