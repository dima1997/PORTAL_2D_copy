#include "../../../includes/textures/common_texture/portal_move_change.h"

#include "../../../includes/textures/common_texture/texture_change.h"
#include "../../../includes/window/window.h"

#include <cstdint>

#include <iostream>

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
    uint32_t idPortal, 
    float newX, 
    float newY, 
    uint32_t idShooter,
    float normalX,
    float normalY
)
:   TextureChange(idPortal),
    idPortal(idPortal),
    newX(newX),
    newY(newY),
    idShooter(idShooter),
    normalX(normalX),
    normalY(normalY) {}

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
    std::cout << "PORTAL : \n";
    std::cout << "New X : " << this->newX << " New Y : "<< this->newY <<" \n";
    std::cout << "Normal X : " << this->normalX << " Normal Y : "<< this->normalY << " \n";
    window.move_texture(this->idPortal, this->newX, this->newY);
    window.point_texture(this->idPortal, this->normalX, this->normalY);
    window.point_texture(this->idShooter, this->newX, this->newY);
}