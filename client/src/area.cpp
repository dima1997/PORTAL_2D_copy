#include "area.h"

#include <utility>

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
Area::Area(int x, int y, int width, int height) :
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
Area Area::adjust(float adjuster){
    int newX = this->x * adjuster;
    int newY = this->y * adjuster;
    int newWidth = this->width * adjuster;
    int newHeight = this->height * adjuster;
    return std::move(Area(newX, newY, newWidth, newHeight)); 
}

/*Devuelve la coordenada (int) x del area*/
int Area::getX() const {
	return this->x;
}

/*Devuelve la coordenada (int) y del area*/
int Area::getY() const {
	return this->y;
}

/*Devuelve el ancho (int) del area*/
int Area::getWidth() const {
	return this->width;
}

/*Devuelve la altura (int) del area*/
int Area::getHeight() const {
	return this->height;
}

