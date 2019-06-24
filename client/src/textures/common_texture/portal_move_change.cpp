#include "../../../includes/textures/common_texture/portal_move_change.h"

#include "../../../includes/textures/common_texture/texture_change.h"
#include "../../../includes/window/window.h"

#include <protocol/event/portal_moves_event.h>
#include <connector/connector.h>

#include <cstdint>

/*
PRE: Recibe un connector por donde se vaya a recibir a 
continuacion un PortalMoveEvent.
POST: Inicializa un cambio de portal moviendose.
*/
PortalMoveChange::PortalMoveChange(Connector & connector)
:   TextureChange(0) {
    PortalMovesEvent event;
    connector >> event;
    this->idPortal = event.getId(); 
    this->newX = event.getX();
    this->newY = event.getY();
    this->idShooter = event.get_chell_id();
    this->normalX = event.get_normal_x();
    this->normalY = event.get_normal_y();
}

/*
Destruye el cambio de ubicacion de la textura 
del portal.
*/
PortalMoveChange::~PortalMoveChange() = default;

/*
PRE: Recibe un ventana (Window &) donde 
realizar el cambio.
POST: Realiza el cambio que representa 
en la ventana recibida.
*/
void PortalMoveChange::change(Window & window){
    window.move_texture(this->idPortal, this->newX, this->newY);
    window.point_texture(this->idPortal, this->normalX, this->normalY);
    window.point_texture(this->idShooter, this->newX, this->newY);
}