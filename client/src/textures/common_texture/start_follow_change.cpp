#include "../../../includes/textures/common_texture/start_follow_change.h"

#include "../../../includes/textures/common_texture/texture_change.h"
#include "../../../includes/window/window.h"

#include <cstdint>

/*
PRE: Recibe:
    el id de una textura seguidora;
    el id de una textura a seguir;
POST: Inicializa un cambio de empezar a seguir
una textura.
*/
StartFollowChange::StartFollowChange(
    uint32_t idFollowing, 
    uint32_t idFollowed
)
:   TextureChange(idFollowing),
    idFollowing(idFollowing),
    idFollowed(idFollowed) {}

/*
Destruye el cambio de seguimiento de la textura.
*/
StartFollowChange::~StartFollowChange() = default;

/*
PRE: Recibe un ventana (Window &) donde 
realizar el cambio.
POST: Realiza el cambio que representa 
en la ventana recibida.
*/
void StartFollowChange::change(Window &window){
    window.start_follow(this->idFollowing, this->idFollowed);
}  