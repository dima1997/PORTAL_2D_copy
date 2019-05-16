#include "area.h"

/*
PRE: Recibe unas coordenadas x,y donde se 
posicionara el area, y el ancho y largo 
del mismo (todo int).
POST: Inicializa un area.
*/
Area::Area(int x, int y, int width, int height) :
	x(x), y(y), width(width), height(height){
}

/*Destruye un area*/
Area::~Area(){}

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
