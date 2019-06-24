#include "../../../includes/textures/common_texture/start_game_change.h"

#include "../../../includes/textures/common_texture/texture_change.h"
#include "../../../includes/threads/play_result.h"
#include "../../../includes/threads/key_reader.h"
#include "../../../includes/window/window.h"

#include <connector/connector.h>

/*
PRE: Recibe un connector.
POST: Inicializa un cambio de inicio 
de partida.
*/
StartGameChange::StartGameChange(Connector & connector)
:   TextureChange(0){
    //No necesita recibir nada 
}

/*
Destruye el cambio.
*/
StartGameChange::~StartGameChange() = default;

/*
Habilita deshabilita la pantalla de partida 
cargando, y habilita todo el input del 
usuario.
*/
void StartGameChange::change(
    Window & window, 
    PlayResult & playResult, 
    KeyReader & keyReader
)
{
    window.switch_loading_texture();
    keyReader.set_alive_keys();
}