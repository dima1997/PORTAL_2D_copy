#include "texture.h"

#include "area.h"

/*
Pre: Recibe un factor de ajuste (pixeles/<unidad de mapa>), 
y una referencia constante al area de la camara en el mapa 
(en unidades y sistema de referencia del mapa) de juego, 
que indica que objetos del mismo se visualizan en la 
ventana.
POST: Devuelve el area de destino de la textura, en la ventana, 
con respecto a la misma.
*/
Area Texture::getAreaDest(float adjustes, const Area & areaCamera) {
    Area areaCameraTopLeft = areaCamera.from_center_to_top_left(); 
    Area dest = this->areaMap.from_center_to_top_left();
    dest = dest.to_y_axis_down_reference_system(
                    areaCameraTopLeft.getX(), areaCameraTopLeft.getY());
    dest = dest.adjust(adjuster);
    return std::move(dest);
}

/*
PRE: Recibe una referencia a una gran textura que 
contiene la imagen donde se encuentra el/los sprite/s 
que utiliza la textura; el area (Area) que ocupa el 
objeto que representa la textura en el mapa de juego;
y un puntero unico con el sprite strategy que utiliza 
la textura para ir variando sus sprites.
POST: 
*/
Texture::Texture(BigTexture & bigTexture, Area areaMap, 
    std::unique_ptr<SpriteStrategy> ptrSpriteStrategy);

/*Destruye la textura.*/
Texture::~Texture() = default;

/*
PRE: Recibe la coordenadas (float) x,y donde se desplaza 
la textura.
POST: Desplaza la textura al posicion indicada, y realiza
cambios en su sprite segun indique el sprite strategy con 
que se creo.
*/
void Texture::move_to(float x, float y){
    float xBefore = this->areaMap.getX();
    float yBefere = this->areaMap.getY();
    float xNow = x;
    float yNow = y;
    this->areaMap.setX(xNow);
    this->areaMap.setX(yNow);
    (*this->ptrSpriteStrategy).move(xBefore, yBefere, xNow, yNow);
}

/*
Realiza un switch en su sprite actual, segun el sprite 
strategy con que se creo.
*/
void Texture::switch(){
    (*this->ptrSpriteStrategy).switch();
}

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
void Texture::render(float adjuster, const Area & areaCamera) {
    if (! this->areaMap.isIntersectedBy(areaCamera)){
        return;
    }
    Area src = (*this->ptrSpriteStrategy).getNextArea();
    Area dest = this->getAreaDest(adjuster, areaCamera);
    this->bigTexture.render(src, dest, NO_FLIP);
}

/*
Retorna un area (Area) de vision nula.
*/
Area Texture::getVisionArea() {
    return std::move(Area(0,0,0,0));
}