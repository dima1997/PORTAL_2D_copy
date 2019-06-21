#include "../../../includes/textures/common_texture/portal_move_change.h"

#include "../../../includes/textures/common_texture/texture_change.h"
#include "../../../includes/window/window.h"

#include <cstdint>

/*
PRE: Recibe:
    el id de una textura de portal;
    las nuevas coordenadas x,y de la misma, en el 
    mapa de juego;
    y el id de la textura quien dispara el portal.
POST: Inicializa un cambio en la ubicacion de la
textura del portal, bajo las condiciones indicadas.
*/
PortalMoveChange::PortalMoveChange(
    uint32_t idTexture, 
    float newX, 
    float newY, 
    uint32_t idShooter
)
:   TextureChange(idTexture),
    newX(newX),
    newY(newY),
    idShooter(idShooter) {}

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
    window.move_texture(this->idTexture, this->newX, this->newY);
    window.point_texture(this->idShooter, this->newX, this->newY);
}