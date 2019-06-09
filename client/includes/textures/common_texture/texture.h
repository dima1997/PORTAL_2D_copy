#ifndef TEXTURE_H
#define TEXTURE_H

#include "../../../includes/mixer/mixer.h"

#include "area.h"
#include "big_texture.h"
#include "sprite_strategy.h" 

#include <memory>

class Texture {
protected:
    BigTexture & bigTexture;
    Area areaMap;
    std::unique_ptr<SpriteStrategy> ptrSpriteStrategy;

    /*
    Pre: Recibe un factor de ajuste (pixeles/<unidad de mapa>), 
    y una referencia constante al area de la camara en el mapa 
    (en unidades y sistema de referencia del mapa) de juego, 
    que indica que objetos del mismo se visualizan en la 
    ventana.
    POST: Devuelve el area de destino de la textura, en la ventana, 
    con respecto a la misma.
    */
    Area getAreaDest(float adjustes, const Area & areaCamera);

public:
    /*
    PRE: Recibe una referencia a una gran textura que 
    contiene la imagen donde se encuentra el/los sprite/s 
    que utiliza la textura; el area (Area) que ocupa el 
    objeto que representa la textura en el mapa de juego;
    y un puntero unico con el sprite strategy que utiliza 
    la textura para ir variando sus sprites.
    POST: 
    */
    Texture(BigTexture & bigTexture, Area areaMap, 
        std::unique_ptr<SpriteStrategy> ptrSpriteStrategy);

    /*Destruye la textura.*/
    virtual ~Texture();

    /*
    PRE: Recibe la coordenadas (float) x,y donde se desplaza 
    la textura.
    POST: Desplaza la textura al posicion indicada, y realiza
    cambios en su sprite segun indique el sprite strategy con 
    que se creo.
    */
    virtual void move_to(float x, float y);
    /*
    Realiza un switch en su sprite actual, segun el sprite 
    strategy con que se creo.
    */
    virtual void switch_sprite();

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
    Retorna un area (Area) de vision nula.
    */
    virtual Area getVisionArea();

    /*
    Devuelve una referencia constante al area (const Area &) de la 
    textura en el mapa del juego.
    */
    const Area & getAreaMap();

    /*
    No reproduce ningun efecto de sonido. 
    */
    virtual void sound(Mixer & mixer);
};

#endif // TEXTURE_H
