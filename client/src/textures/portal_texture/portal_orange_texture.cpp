#include "../../../includes/textures/portal_texture/portal_orange_texture.h"

#include "../../../includes/textures/portal_texture/portal_sprite_strategy.h"
#include "../../../includes/textures/common_texture/area.h"
#include "../../../includes/textures/common_texture/big_texture.h"
#include "../../../includes/textures/common_texture/texture.h"
#include "../../../includes/textures/common_texture/sprite_strategy.h"

#include <memory>

/*
PRE: Recibe una gran textura que contiene de la imagen PORTAL_SPRITES 
de images_paths.h; y el area del mapa de juego que representa esta 
textura.
POST: Inicializa una texture de portal naranja.
*/
PortalOrangeTexture::PortalOrangeTexture(BigTexture & bigTexture, Area areaMap) 
:    Texture(bigTexture, areaMap, 
        std::move(
            std::unique_ptr<SpriteStrategy>(new PortalSpriteStrategy())
        )
    ) {}

/*Destruye la textura del portal naranja.*/
PortalOrangeTexture::~PortalOrangeTexture() = default;

/*
Pre: Recibe un factor de ajuste (pixeles/<unidad de mapa>), 
y una referencia constante al area de la camara en el mapa 
(en unidades y sistema de referencia del mapa) de juego, 
que indica que objetos del mismo se visualizan en la 
ventana.
POST: Renderiza la textura si es que alguna parte de la misma 
se encuentra en el area de la camera recibida, ajustando las 
dimensiones de la textura a pixeles, con el factor recibido.
*/
void PortalOrangeTexture::render(float adjuster, const Area & areaCamera) {
    Area src = (*this->ptrSpriteStrategy).getNextArea();
    if (! this->areaMap.isIntersectedBy(areaCamera)){
        return;
    }
    Area dest = this->getAreaDest(adjuster, areaCamera);
    this->bigTexture.render(src, dest, NO_FLIP, 0, 255, 100, 1);
}
