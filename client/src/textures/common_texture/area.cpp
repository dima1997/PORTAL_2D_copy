#include "../../../includes/textures/common_texture/area.h"

#include <utility>
#include <tuple>

/*
Construye un area de coordenadas y dimensiones cero.
*/
Area::Area() : x(0), y(0), width(0), height(0) {}

/*
PRE: Recibe unas coordenadas x,y donde se 
posicionara el area, y el ancho y largo 
del mismo (todos int).
POST: Inicializa un area.
*/
Area::Area(float x, float y, float width, float height) :
	x(x), y(y), width(width), height(height){
}

/*Destruye un area*/
Area::~Area(){}

/*
PRE: Recibe una doble referencia a otra area (Area &&).
POST: Inicializa una nueva area por movimiento semantico.
El area recibida queda en estado nulo.
*/
Area::Area(Area && otherArea){
    this->x = otherArea.x;
    this->y = otherArea.y;
    this->width = otherArea.width;
    this->height = otherArea.height;
    otherArea.x = 0;
    otherArea.y = 0;
    otherArea.width = 0;
    otherArea.height = 0;
}

/*
PRE: Recibe una doble referencia a otra area (Area &&).
POST: Realiza una asignacion por movimiento semantico. 
Devuelve una referencia al area actual.
El area recibida queda en estado nulo.
*/
Area & Area::operator=(Area && otherArea){
    if (this == &otherArea){
        return *this;
    }
    this->x = otherArea.x;
    this->y = otherArea.y;
    this->width = otherArea.width;
    this->height = otherArea.height;
    otherArea.x = 0;
    otherArea.y = 0;
    otherArea.width = 0;
    otherArea.height = 0;
    return *this;
}

/*
PRE: Recibe una referencia constante a otra area (const Area &).
POST: Inicializa una nueva area por copia.
*/
Area::Area(const Area &otherArea){
    this->x = otherArea.x;
    this->y = otherArea.y;
    this->width = otherArea.width;
    this->height = otherArea.height;
}

/*
PRE: Recibe una referencia constante a otra area (const Area &).
POST: Realiza una asignacion por copia. Devuelve una referencia al
area actual
*/
Area & Area::operator=(const Area &otherArea){
    if (this == &otherArea){
        return *this;
    }
    this->x = otherArea.x;
    this->y = otherArea.y;
    this->width = otherArea.width;
    this->height = otherArea.height;
    return *this;
}

/*
PRE: Recibe un factor de ajuste (<nueva unidad>/<unidad actual>)
POST: Devuelve un nuevo area (Area) que ajusta la medidas del actual.
*/
Area Area::adjust(float adjuster) const {
    float newX = this->x * adjuster;
    float newY = this->y * adjuster;
    float newWidth = this->width * adjuster;
    float newHeight = this->height * adjuster;
    return std::move(Area(newX, newY, newWidth, newHeight)); 
}

/*
Devuelve un nuevo area con las coordenadas de su 
actual esquina superior izquierda (relativo 
al sistema de referencia usado).
(Superior => y mas grande)
(Izquieda => x mas chico)
*/
Area Area::from_center_to_top_left() const {
    float xCenter = this->getX();
    float yCenter = this->getY();
    float width = this->getWidth();
    float height = this->getHeight();
    float xTopLeft = xCenter - (width/2);
    float yTopLeft = yCenter + (height/2);
    return std::move(Area(xTopLeft,yTopLeft,width,height)); 
}

/*
PRE: Recibe las coordenadas (float) x,y del sistema de 
referencia actual, que seran utilizadas como origen de 
coordenadas del nuevo sistema de referencia, que tiene
el eje de coordenadas Y, al reves del actual.
POST: Devuelve un nuevo area (Area) con las coordenadas
adaptadas al nuevo sistema de referencia.
*/
Area Area::to_y_axis_down_reference_system
(float xOrigin, float yOrigin) const {
    float newX = this->x - xOrigin;
    float newY = - (this->y - yOrigin);
    return std::move(Area(newX, newY, this->width, this->height));
}


/*Devuelve la coordenada (float) x del area*/
float Area::getX() const {
    return this->x;
}

/*Devuelve la coordenada (float) y del area*/
float Area::getY() const {
    return this->y;
}

/*Devuelve el ancho (float) del area*/
float Area::getWidth() const {
    return this->width;
}

/*Devuelve la altura (float) del area*/
float Area::getHeight() const {
    return this->height;
}

/*
Devuelve un vector de floats (std::vector<float>) con las coordenadas 
extremas del area, suponiendo que la misma tiene sus coordenadas en el
centro de la misma. 
El orden de las coordenadas devueltas es el siguiente:
xButton, xTop, yButton, yTop . 
*/
std::tuple<float,float,float,float> Area::getExtremeCoords() const {
    float xBottom = this->getX() - (this->getWidth()/2);
    float xTop = this->getX() + (this->getWidth()/2);
    float yButton = this->getY() - (this->getHeight()/2);
    float yTop = this->getY() + (this->getHeight()/2);
    std::tuple<float,float,float,float> extremeCoords(
                                            xBottom,xTop,yButton,yTop);
    return std::move(extremeCoords);

}

/*
PRE: Recibe una referencia constante a otra area (const Area &).
POST: Devuele true, si ambas areas se intersecan en algun punto;
false en caso contrario.
*/
bool Area::isIntersectedBy(const Area & otherArea) const {
    float myXBotton, myXTop, myYBotton, myYTop;
    std::tie(myXBotton, myXTop, myYBotton, myYTop) = this->getExtremeCoords();
    float otherXBotton, otherXTop, otherYBotton, otherYTop;
    std::tie(otherXBotton, otherXTop, otherYBotton, otherYTop) = 
                                                otherArea.getExtremeCoords(); 
    // myXBotton < myXtop < otherXBotton < otherXTop
    // ||
    // otherXBotton < otherXtop < myXBotton < myXTop                                                  
    if ((myXTop < otherXBotton) || (otherXTop < myXBotton)){
        return false;
    }
    // Entonces hay interseccion en el eje X
    // Misma comparacion pero en el eje Y
    if ((myYTop < otherYBotton) || (otherYTop < myYBotton)){
        return false;
    }
    //Entonces hay interseccion en el eje Y, tambien
    //Entonces la interseccion no es vacio.
    return true;    
}

/*
PRE: Recibe una nueva coordanada (float) x.
POST: Cambia el valor de coordenada x del area 
por el recibido.
*/
void Area::setX(float x) {
    this-> x = x;
}

/*
PRE: Recibe una nueva coordanada (float) y.
POST: Cambia el valor de coordenada y del area 
por el recibido.
*/
void Area::setY(float y) {
    this->y = y;
}

