#ifndef TEXTURE_H
#define TEXTURE_H

#include "../../../includes/mixer/mixer.h"
#include "../../../includes/mixer/sounds_path.h"

#include "area.h"
#include "big_texture.h"
#include "sprite_strategy.h" 

#include <memory>

class Texture {
protected:
    BigTexture & bigTexture;
    Area areaMap;
    std::unique_ptr<SpriteStrategy> ptrSpriteStrategy;
    std::vector<SOUND_NAME> sounds;
    bool following;
    const Area * ptrFollowArea;
    double angle;

    /*
    Pre: Recibe un factor de ajuste (pixeles/<unidad de mapa>), 
    y una referencia constante al area de la camara en el mapa 
    (en unidades y sistema de referencia del mapa) de juego, 
    que indica que objetos del mismo se visualizan en la 
    ventana.
    POST: Devuelve el area de destino de la textura, en la ventana, 
    con respecto a la misma.
    */
    virtual Area getAreaDest(float adjustes, const Area & areaCamera);

public:
    /*
    PRE: Recibe una referencia a una gran textura que 
    contiene la imagen donde se encuentra el/los sprite/s 
    que utiliza la textura; el area (Area) que ocupa el 
    objeto que representa la textura en el mapa de juego;
    y un puntero unico con el sprite strategy que utiliza 
    la textura para ir variando sus sprites.
    POST: Inicializa una textura.
    */
    Texture(BigTexture & bigTexture, Area areaMap, 
        std::unique_ptr<SpriteStrategy> ptrSpriteStrategy);

    /*
    PRE: Recibe una referencia a una gran textura que 
    contiene la imagen donde se encuentra el/los sprite/s 
    que utiliza la textura; el area (Area) que ocupa el 
    objeto que representa la textura en el mapa de juego;
    y sprite dinamico que sera el unico sprite a usar en la
    vida de la textura.
    POST: Inicializa una textura.
    */
    Texture(BigTexture & bigTexture, Area areaMap, 
        DynamicSprite dynamicSprite);

    /*
    PRE: Recibe:
        una referencia a una gran textura que 
        contiene la imagen donde se encuentra el/los sprite/s 
        que utiliza la textura; 
        el area (Area) que ocupa el objeto que representa la 
        textura en el mapa de juego;
        el sprite dinamico que sera el unico sprite a usar en la
        vida de la textura;
        un angulo (double) para rotar la textura al renderizarla.
    POST: Inicializa una textura.
    */
    Texture(
        BigTexture & bigTexture, 
        Area areaMap, 
        DynamicSprite dynamicSprite,
        double angle
    );

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
    virtual const Area & get_area_map();

    /*
    Reproduce los sonidos que la textura tiene guardados.
    */
    virtual void sound(Mixer & mixer);

    /*
    PRE: Recibe una referencia constante a un area (const Area &).
    POST: Ahora el area del mapa de esta textura, copia las 
    coordenadas del area recibida, cada vez que se renderiza.
    */
    void follow_area(const Area & areaMap);

    /*Deja de seguir al area que sigue.*/
    void stop_follow();


    /*Actualiza la textura.*/
    virtual void update();
};

#endif // TEXTURE_H
