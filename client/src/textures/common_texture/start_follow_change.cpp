#include "../../../includes/textures/common_texture/start_follow_change.h"

#include "../../../includes/textures/common_texture/texture_change.h"
#include "../../../includes/window/window.h"

#include <connector/connector.h>
#include <protocol/event/grab_rock_event.h>

#include <cstdint>

/*
PRE: Recibe un connector que recibira a continuacion:
    el id de una textura seguidora;
    luego, el id de una textura a seguir;
POST: Inicializa un cambio de empezar a seguir
una textura.
*/
StartFollowChange::StartFollowChange(Connector & connector)
:   TextureChange(0) {
    GrabRockEvent event(0,0);
    connector >> event;
    this->idFollowed = event.getChellId();
    this->idFollowing = event.getRockId();
}

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