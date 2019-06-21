#include "../../../includes/textures/common_texture/stop_follow_change.h"

#include "../../../includes/textures/common_texture/texture_change.h"
#include "../../../includes/window/window.h"

#include <cstdint>

/*
PRE: Recibe:
    el id de una textura seguidora;
    el id de una textura a seguir;
POST: Inicializa un cambio de dejar de seguir
una textura.
*/
StopFollowChange::StopFollowChange(
    uint32_t idFollowing 
)
:   TextureChange(idFollowing) {}

/*
Destruye el cambio de seguimiento de la textura.
*/
StopFollowChange::~StopFollowChange() = default;

/*
PRE: Recibe un ventana (Window &) donde 
realizar el cambio.
POST: Realiza el cambio que representa 
en la ventana recibida.
*/
void StopFollowChange::change(Window &window){
    window.stop_follow(this->id);
}  