#ifndef PORTAL_ORANGE_TEXTURE_H
#define PORTAL_ORANGE_TEXTURE_H

#include "../common_texture/texture.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"

class PortalOrangeTexture : public Texture {
public:
    /*
    PRE: Recibe una gran textura que contiene de la imagen 
    PORTAL_SPRITE de images_path.h; y el area
    del mapa de juego que representa esta textura.
    POST: Inicializa una textura de portal naranja.
    */
    PortalOrangeTexture(BigTexture & bigTexture, Area areaMap);

    /*Destruye la textura del portal naranja.*/
    virtual ~PortalOrangeTexture();

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
    virtual void render(float adjuster, const Area & areaCamera);

    /*
    PRE: Recibe la coordenadas (float) x,y donde se desplaza 
    la textura.
    POST: Desplaza la textura al posicion indicada, y realiza
    cambios en su sprite segun indique el sprite strategy con 
    que se creo.
    */
    virtual void move_to(float x, float y);
};

#endif // PORTAL_ORANGE_TEXTURE_H
